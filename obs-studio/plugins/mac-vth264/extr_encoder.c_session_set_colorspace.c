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
typedef  enum video_colorspace { ____Placeholder_video_colorspace } video_colorspace ;
typedef  int /*<<< orphan*/  VTCompressionSessionRef ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  int /*<<< orphan*/ * CFStringRef ;

/* Variables and functions */
 int /*<<< orphan*/  SESSION_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kCVImageBufferColorPrimaries_ITU_R_709_2 ; 
 int /*<<< orphan*/ * kCVImageBufferTransferFunction_ITU_R_709_2 ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_ColorPrimaries ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_TransferFunction ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_YCbCrMatrix ; 
 int /*<<< orphan*/  noErr ; 
 int /*<<< orphan*/ * obs_to_vt_colorspace (int) ; 
 int /*<<< orphan*/  session_set_prop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static OSStatus session_set_colorspace(VTCompressionSessionRef session,
				       enum video_colorspace cs)
{
	CFStringRef matrix = obs_to_vt_colorspace(cs);
	OSStatus code;

	if (matrix != NULL) {
		SESSION_CHECK(session_set_prop(
			session, kVTCompressionPropertyKey_ColorPrimaries,
			kCVImageBufferColorPrimaries_ITU_R_709_2));
		SESSION_CHECK(session_set_prop(
			session, kVTCompressionPropertyKey_TransferFunction,
			kCVImageBufferTransferFunction_ITU_R_709_2));
		SESSION_CHECK(session_set_prop(
			session, kVTCompressionPropertyKey_YCbCrMatrix,
			matrix));
	}

	return noErr;
}