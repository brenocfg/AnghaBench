#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  double uint8_t ;
typedef  int uint32_t ;
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  scalar_t__ cmsColorSpaceSignature ;

/* Variables and functions */
 int BYTES_SH (int) ; 
 int CHANNELS_SH (int) ; 
 int COLORSPACE_SH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_ANY ; 
 int /*<<< orphan*/  PT_Lab ; 
 int /*<<< orphan*/  TYPE_BGR_8 ; 
 scalar_t__ T_BYTES (int) ; 
 int cmsChannelsOf (scalar_t__) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateTransform (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsCreate_sRGBProfile () ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,double*,double*,int) ; 
 scalar_t__ cmsGetColorSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsOpenProfileFromMem (double const*,size_t) ; 
 scalar_t__ cmsSigLabData ; 

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  cmsHPROFILE srcProfile = cmsOpenProfileFromMem(data, size);
  if (!srcProfile) return 0;

  cmsHPROFILE dstProfile = cmsCreate_sRGBProfile();
  if (!dstProfile) {
    cmsCloseProfile(srcProfile);
    return 0;
  }

  cmsColorSpaceSignature srcCS = cmsGetColorSpace(srcProfile);
  cmsUInt32Number nSrcComponents = cmsChannelsOf(srcCS);
  cmsUInt32Number srcFormat;
  if (srcCS == cmsSigLabData) {
    srcFormat =
        COLORSPACE_SH(PT_Lab) | CHANNELS_SH(nSrcComponents) | BYTES_SH(0);
  } else {
    srcFormat =
        COLORSPACE_SH(PT_ANY) | CHANNELS_SH(nSrcComponents) | BYTES_SH(1);
  }

  cmsUInt32Number intent = 0;
  cmsUInt32Number flags = 0;
  cmsHTRANSFORM hTransform = cmsCreateTransform(
      srcProfile, srcFormat, dstProfile, TYPE_BGR_8, intent, flags);
  cmsCloseProfile(srcProfile);
  cmsCloseProfile(dstProfile);
  if (!hTransform) return 0;

  uint8_t output[4];
  if (T_BYTES(srcFormat) == 0) {  // 0 means double
    double input[nSrcComponents];
    for (uint32_t i = 0; i < nSrcComponents; i++) input[i] = 0.5f;
    cmsDoTransform(hTransform, input, output, 1);
  } else {
    uint8_t input[nSrcComponents];
    for (uint32_t i = 0; i < nSrcComponents; i++) input[i] = 128;
    cmsDoTransform(hTransform, input, output, 1);
  }
  cmsDeleteTransform(hTransform);

  return 0;
}