#include "jni.h"
#include "libyuv.h"

#include "jni-macros.h"

using namespace libyuv;

#define FROM_1_1( NAME, S,                 D) \
  PLANES_1_TO_1(  NAME, S,                 D)
#define FROM_2_1( NAME, S, S1, S2,         D) \
  PLANES_2_TO_1(  NAME,    S1, S2,         D) \
  PLANES_2P_TO_1( NAME, S, S1, S2,         D)
#define FROM_3_1( NAME, S, S1, S2, S3, SY, D) \
  PLANES_3_TO_1(  NAME,    S1, S2, S3,     D) \
  PLANES_3P_TO_1( NAME, S, S1, S2, S3, SY, D)
#define FROM_1_2( NAME, S,                 D, D1, D2) \
  PLANES_1_TO_2(  NAME, S,                    D1, D2) \
  PLANES_1_TO_2P( NAME, S,                 D, D1, D2)
#define FROM_2_2( NAME, S, S1, S2,         D, D1, D2) \
  PLANES_2_TO_2(  NAME,    S1, S2,            D1, D2) \
  PLANES_2P_TO_2( NAME, S, S1, S2,            D1, D2) \
  PLANES_2_TO_2P( NAME,    S1, S2,         D, D1, D2) \
  PLANES_2P_TO_2P(NAME, S, S1, S2,         D, D1, D2)
#define FROM_3_2( NAME, S, S1, S2, S3, SY, D, D1, D2) \
  PLANES_3_TO_2(  NAME,    S1, S2, S3,        D1, D2) \
  PLANES_3P_TO_2( NAME, S, S1, S2, S3, SY,    D1, D2) \
  PLANES_3_TO_2P( NAME,    S1, S2, S3,     D, D1, D2) \
  PLANES_3P_TO_2P(NAME, S, S1, S2, S3, SY, D, D1, D2)
#define FROM_1_3( NAME, S,                 D, D1, D2, D3, DY) \
  PLANES_1_TO_3(  NAME, S,                    D1, D2, D3)     \
  PLANES_1_TO_3P( NAME, S,                 D, D1, D2, D3, DY)
#define FROM_2_3( NAME, S, S1, S2,         D, D1, D2, D3, DY) \
  PLANES_2_TO_3(  NAME,    S1, S2,            D1, D2, D3)     \
  PLANES_2P_TO_3( NAME, S, S1, S2,            D1, D2, D3)     \
  PLANES_2_TO_3P( NAME,    S1, S2,         D, D1, D2, D3, DY) \
  PLANES_2P_TO_3P(NAME, S, S1, S2,         D, D1, D2, D3, DY)
#define FROM_3_3( NAME, S, S1, S2, S3, SY, D, D1, D2, D3, DY) \
  PLANES_3_TO_3(  NAME,    S1, S2, S3,        D1, D2, D3)     \
  PLANES_3P_TO_3( NAME, S, S1, S2, S3, SY,    D1, D2, D3)     \
  PLANES_3_TO_3P( NAME,    S1, S2, S3,     D, D1, D2, D3, DY) \
  PLANES_3P_TO_3P(NAME, S, S1, S2, S3, SY, D, D1, D2, D3, DY)

#define COPY_1(NAME, P)                 FROM_1_1(NAME, P,                 P)
#define COPY_2(NAME, P, P1, P2)         FROM_3_2(NAME, P, P1, P2,         P, P1, P2)
#define COPY_3(NAME, P, P1, P2, P3, PY) FROM_3_3(NAME, P, P1, P2, P3, PY, P, P1, P2, P3, PY)

// Conversions to I420

#define FROM_1_I420(NAME, S)                 FROM_1_3(NAME, S,                 I420, Y, U, V, 2)
#define FROM_2_I420(NAME, S, S1, S2)         FROM_2_3(NAME, S, S1, S2,         I420, Y, U, V, 2)
#define FROM_3_I420(NAME, S, S1, S2, S3, SY) FROM_3_3(NAME, S, S1, S2, S3, SY, I420, Y, U, V, 2)

COPY_3(     I420Copy,       I420, Y, U, V, 2);
FROM_3_I420(I422ToI420,     I422, Y, U, V, 1);
FROM_3_I420(I444ToI420,     I444, Y, U, V, 1);
FROM_3_I420(I411ToI420,     I411, Y, U, V, 1);
FROM_1_I420(I400ToI420,     Y);
FROM_2_I420(NV12ToI420,     NV12, Y, UV);
FROM_2_I420(NV21ToI420,     NV21, Y, VU);
FROM_1_I420(YUY2ToI420,     YUY2);
FROM_1_I420(UYVYToI420,     UYVY);
FROM_1_I420(M420ToI420,     M420);
FROM_2_I420(Q420ToI420,     Q420, Y, YUY2);
FROM_1_I420(ARGBToI420,     ARGB);
FROM_1_I420(BGRAToI420,     BGRA);
FROM_1_I420(ABGRToI420,     ABGR);
FROM_1_I420(RGBAToI420,     RGBA);
FROM_1_I420(RGB24ToI420,    RGB24);
FROM_1_I420(RAWToI420,      RAW);
FROM_1_I420(RGB565ToI420,   RGB565);
FROM_1_I420(ARGB1555ToI420, ARGB1555);
FROM_1_I420(ARGB4444ToI420, ARGB4444);

// Conversions to ARGB

#define FROM_1_ARGB(NAME, S)                 FROM_1_1(NAME, S,                 ARGB)
#define FROM_2_ARGB(NAME, S, S1, S2)         FROM_2_1(NAME, S, S1, S2,         ARGB)
#define FROM_3_ARGB(NAME, S, S1, S2, S3, SY) FROM_3_1(NAME, S, S1, S2, S3, SY, ARGB)

FROM_3_ARGB(I420ToARGB,     I420, Y, U, V, 2);
FROM_3_ARGB(I422ToARGB,     I422, Y, U, V, 1);
FROM_3_ARGB(I444ToARGB,     I444, Y, U, V, 1);
FROM_3_ARGB(I411ToARGB,     I411, Y, U, V, 1);
FROM_1_ARGB(I400ToARGB,     Y);
FROM_2_ARGB(NV12ToARGB,     NV12, Y, UV);
FROM_2_ARGB(NV21ToARGB,     NV21, Y, VU);
FROM_1_ARGB(YUY2ToARGB,     YUY2);
FROM_1_ARGB(UYVYToARGB,     UYVY);
FROM_1_ARGB(M420ToARGB,     M420);
// No Q420ToARGB
COPY_1(     ARGBCopy,       ARGB);
FROM_1_ARGB(BGRAToARGB,     BGRA);
FROM_1_ARGB(ABGRToARGB,     ABGR);
FROM_1_ARGB(RGBAToARGB,     RGBA);
FROM_1_ARGB(RGB24ToARGB,    RGB24);
FROM_1_ARGB(RAWToARGB,      RAW);
FROM_1_ARGB(RGB565ToARGB,   RGB565);
FROM_1_ARGB(ARGB1555ToARGB, ARGB1555);
FROM_1_ARGB(ARGB4444ToARGB, ARGB4444);

// Conversions from I420

#define FROM_I420_1(NAME, D)                 FROM_3_1(NAME, I420, Y, U, V, 2, D)
#define FROM_I420_2(NAME, D, D1, D2)         FROM_3_2(NAME, I420, Y, U, V, 2, D, D1, D2)
#define FROM_I420_3(NAME, D, D1, D2, D3, DY) FROM_3_3(NAME, I420, Y, U, V, 2, D, D1, D2, D3, DY)

// = I420Copy
FROM_I420_3(I420ToI422,     I422, Y, U, V, 1);
FROM_I420_3(I420ToI444,     I444, Y, U, V, 1);
FROM_I420_3(I420ToI411,     I411, Y, U, V, 1);
// = I400Copy
FROM_I420_2(I420ToNV12,     NV12, Y, UV);
FROM_I420_2(I420ToNV21,     NV21, Y, VU);
FROM_I420_1(I420ToYUY2,     YUY2);
FROM_I420_1(I420ToUYVY,     UYVY);
// No I420ToM420
// No I420ToQ420
// = I420ToARGB
FROM_I420_1(I420ToBGRA,     BGRA);
FROM_I420_1(I420ToABGR,     ABGR);
FROM_I420_1(I420ToRGBA,     RGBA);
FROM_I420_1(I420ToRGB24,    RGB24);
FROM_I420_1(I420ToRAW,      RAW);
FROM_I420_1(I420ToRGB565,   RGB565);
FROM_I420_1(I420ToARGB1555, ARGB1555);
FROM_I420_1(I420ToARGB4444, ARGB4444);

// Conversions from ARGB

#define FROM_ARGB_1(NAME, D)                 FROM_1_1(NAME, ARGB, D)
#define FROM_ARGB_2(NAME, D, D1, D2)         FROM_1_2(NAME, ARGB, D, D1, D2)
#define FROM_ARGB_3(NAME, D, D1, D2, D3, DY) FROM_1_3(NAME, ARGB, D, D1, D2, D3, DY)

// = ARGBToI420
FROM_ARGB_3(ARGBToI422,     I422, Y, U, V, 1);
FROM_ARGB_3(ARGBToI444,     I444, Y, U, V, 1);
FROM_ARGB_3(ARGBToI411,     I411, Y, U, V, 1);
FROM_ARGB_1(ARGBToI400,     Y);
FROM_ARGB_2(ARGBToNV12,     NV12, Y, UV);
FROM_ARGB_2(ARGBToNV21,     NV21, Y, UV);
FROM_ARGB_1(ARGBToYUY2,     YUY2);
FROM_ARGB_1(ARGBToUYVY,     UYVY);
// No ARGBToM420
// No ARGBToQ420
// = ARGBCopy
// = BGRAToARGB
// = ABGRToARGB
FROM_ARGB_1(ARGBToRGBA,     RGBA);
FROM_ARGB_1(ARGBToRGB24,    RGB24);
FROM_ARGB_1(ARGBToRAW,      RAW);
FROM_ARGB_1(ARGBToRGB565,   RGB565);
FROM_ARGB_1(ARGBToARGB1555, ARGB1555);
FROM_ARGB_1(ARGBToARGB4444, ARGB4444);

// Other planar YUV conversions

COPY_3(  I422Copy,     I422, Y, U, V, 1);
COPY_3(  I444Copy,     I444, Y, U, V, 1);
COPY_1(  I400Copy,     Y);
FROM_2_1(NV12ToRGB565, NV12, Y, UV, RGB565);
FROM_2_1(NV21ToRGB565, NV21, Y, VU, RGB565);

#ifdef __cplusplus
extern "C" {
#endif

#define JNI_FROM_1_1(NAME) JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE)
#define JNI_FROM_2_1(NAME) \
  JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE JNI_PLANE), \
  { #NAME, "(" JNI_BUF "II" JNI_PLANE "II)V", (void*) JVM_ ## NAME ## _S }
#define JNI_FROM_3_1(NAME) \
  JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE), \
  { #NAME, "(" JNI_BUF "III" JNI_PLANE "II)V", (void*) JVM_ ## NAME ## _S }
#define JNI_FROM_1_2(NAME) \
  JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE JNI_PLANE), \
  { #NAME, "(" JNI_PLANE JNI_BUF "II" "II)V", (void*) JVM_ ## NAME ## _D }
#define JNI_FROM_2_2(NAME) \
  JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE), \
  { #NAME, "(" JNI_BUF "II" JNI_PLANE JNI_PLANE "II)V", (void*) JVM_ ## NAME ## _S }, \
  { #NAME, "(" JNI_PLANE JNI_PLANE JNI_BUF "II" "II)V", (void*) JVM_ ## NAME ## _D }, \
  { #NAME, "(" JNI_BUF "II" JNI_BUF "II" "II)V", (void*) JVM_ ## NAME ## _SD }
#define JNI_FROM_3_2(NAME) \
  JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE), \
  { #NAME, "(" JNI_BUF "III" JNI_PLANE JNI_PLANE "II)V", (void*) JVM_ ## NAME ## _S }, \
  { #NAME, "(" JNI_PLANE JNI_PLANE JNI_PLANE JNI_BUF "II" "II)V", (void*) JVM_ ## NAME ## _D }, \
  { #NAME, "(" JNI_BUF "III" JNI_BUF "II" "II)V", (void*) JVM_ ## NAME ## _SD }
#define JNI_FROM_1_3(NAME) \
  JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE), \
  { #NAME, "(" JNI_PLANE JNI_BUF "III" "II)V", (void*) JVM_ ## NAME ## _D }
#define JNI_FROM_2_3(NAME) \
  JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE), \
  { #NAME, "(" JNI_BUF "II" JNI_PLANE JNI_PLANE JNI_PLANE "II)V", (void*) JVM_ ## NAME ## _S }, \
  { #NAME, "(" JNI_PLANE JNI_PLANE JNI_BUF "III" "II)V", (void*) JVM_ ## NAME ## _D }, \
  { #NAME, "(" JNI_BUF "II" JNI_BUF "III" "II)V", (void*) JVM_ ## NAME ## _SD }
#define JNI_FROM_3_3(NAME) \
  JNI_CONVERT(NAME, JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE JNI_PLANE), \
  { #NAME, "(" JNI_BUF "III" JNI_PLANE JNI_PLANE JNI_PLANE "II)V", (void*) JVM_ ## NAME ## _S }, \
  { #NAME, "(" JNI_PLANE JNI_PLANE JNI_PLANE JNI_BUF "III" "II)V", (void*) JVM_ ## NAME ## _D }, \
  { #NAME, "(" JNI_BUF "III" JNI_BUF "III" "II)V", (void*) JVM_ ## NAME ## _SD }

static JNINativeMethod methods[] = {
  // Conversions to I420
  JNI_FROM_3_3(I420Copy),
  JNI_FROM_3_3(I444ToI420),
  JNI_FROM_3_3(I422ToI420),
  JNI_FROM_3_3(I411ToI420),
  JNI_FROM_1_3(I400ToI420),
  JNI_FROM_2_3(NV12ToI420),
  JNI_FROM_2_3(NV21ToI420),
  JNI_FROM_1_3(YUY2ToI420),
  JNI_FROM_1_3(UYVYToI420),
  JNI_FROM_1_3(M420ToI420),
  JNI_FROM_2_3(Q420ToI420),
  JNI_FROM_1_3(ARGBToI420),
  JNI_FROM_1_3(BGRAToI420),
  JNI_FROM_1_3(ABGRToI420),
  JNI_FROM_1_3(RGBAToI420),
  JNI_FROM_1_3(RGB24ToI420),
  JNI_FROM_1_3(RAWToI420),
  JNI_FROM_1_3(RGB565ToI420),
  JNI_FROM_1_3(ARGB1555ToI420),
  JNI_FROM_1_3(ARGB4444ToI420),

  // Conversions to ARGB
  JNI_FROM_3_1(I420ToARGB),
  JNI_FROM_3_1(I422ToARGB),
  JNI_FROM_3_1(I444ToARGB),
  JNI_FROM_3_1(I411ToARGB),
  JNI_FROM_1_1(I400ToARGB),
  JNI_FROM_2_1(NV12ToARGB),
  JNI_FROM_2_1(NV21ToARGB),
  JNI_FROM_1_1(M420ToARGB),
  // No Q420ToARGB
  JNI_FROM_1_1(YUY2ToARGB),
  JNI_FROM_1_1(UYVYToARGB),
  JNI_FROM_1_1(ARGBCopy),
  JNI_FROM_1_1(BGRAToARGB),
  JNI_FROM_1_1(ABGRToARGB),
  JNI_FROM_1_1(RGBAToARGB),
  JNI_FROM_1_1(RGB24ToARGB),
  JNI_FROM_1_1(RAWToARGB),
  JNI_FROM_1_1(RGB565ToARGB),
  JNI_FROM_1_1(ARGB1555ToARGB),
  JNI_FROM_1_1(ARGB4444ToARGB),

  // Conversions from I420
  // = I420Copy
  JNI_FROM_3_3(I420ToI422),
  JNI_FROM_3_3(I420ToI444),
  JNI_FROM_3_3(I420ToI411),
  // = I400Copy
  JNI_FROM_3_2(I420ToNV12),
  JNI_FROM_3_2(I420ToNV21),
  JNI_FROM_3_1(I420ToYUY2),
  JNI_FROM_3_1(I420ToUYVY),
  // No I420ToM420
  // No I420ToQ420
  // = I420ToARGB
  JNI_FROM_3_1(I420ToBGRA),
  JNI_FROM_3_1(I420ToABGR),
  JNI_FROM_3_1(I420ToRGBA),
  JNI_FROM_3_1(I420ToRGB24),
  JNI_FROM_3_1(I420ToRAW),
  JNI_FROM_3_1(I420ToRGB565),
  JNI_FROM_3_1(I420ToARGB1555),
  JNI_FROM_3_1(I420ToARGB4444),

  // Conversions from ARGB
  // = ARGBToI420
  JNI_FROM_1_3(ARGBToI422),
  JNI_FROM_1_3(ARGBToI444),
  JNI_FROM_1_3(ARGBToI411),
  JNI_FROM_1_1(ARGBToI400),
  JNI_FROM_1_2(ARGBToNV12),
  JNI_FROM_1_2(ARGBToNV21),
  JNI_FROM_1_1(ARGBToYUY2),
  JNI_FROM_1_1(ARGBToUYVY),
  // No ARGBToM420
  // No ARGBToQ420
  // = ARGBCopy
  // = BGRAToARGB
  // = ABGRToARGB
  JNI_FROM_1_1(ARGBToRGBA),
  JNI_FROM_1_1(ARGBToRGB24),
  JNI_FROM_1_1(ARGBToRAW),
  JNI_FROM_1_1(ARGBToRGB565),
  JNI_FROM_1_1(ARGBToARGB1555),
  JNI_FROM_1_1(ARGBToARGB4444),

  // Other planar YUV conversions
  JNI_FROM_3_3(I422Copy),
  JNI_FROM_3_3(I444Copy),
  JNI_FROM_1_1(I400Copy),
  JNI_FROM_2_1(NV12ToRGB565),
  JNI_FROM_2_1(NV21ToRGB565)
};

jint JNI_OnLoad(JavaVM *vm, void *) {
  JNIEnv *env;
  if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK)
    return JNI_ERR;

  jclass clazz = env->FindClass("fi/gekkio/roboticchameleon/lowlevel/RoboticChameleonJNI");
  if (clazz == NULL)
    return JNI_ERR;

  if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(JNINativeMethod)) < 0)
    return JNI_ERR;

  return JNI_VERSION_1_6;
}

#ifdef __cplusplus
}
#endif
