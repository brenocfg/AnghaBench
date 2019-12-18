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
struct vt_h264_encoder {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  session; } ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  int /*<<< orphan*/  CVPixelBufferRef ;
typedef  int /*<<< orphan*/  CVPixelBufferPoolRef ;
typedef  int /*<<< orphan*/  CFStringRef ;

/* Variables and functions */
 int /*<<< orphan*/  CVBufferSetAttachment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVPixelBufferPoolCreatePixelBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VTCompressionSessionGetPixelBufferPool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCVAttachmentMode_ShouldPropagate ; 
 int /*<<< orphan*/  kCVImageBufferColorPrimariesKey ; 
 int /*<<< orphan*/  kCVImageBufferColorPrimaries_ITU_R_709_2 ; 
 int /*<<< orphan*/  kCVImageBufferTransferFunctionKey ; 
 int /*<<< orphan*/  kCVImageBufferTransferFunction_ITU_R_709_2 ; 
 int /*<<< orphan*/  kCVImageBufferYCbCrMatrixKey ; 
 int kCVReturnError ; 
 int /*<<< orphan*/  obs_to_vt_colorspace (int /*<<< orphan*/ ) ; 

bool get_cached_pixel_buffer(struct vt_h264_encoder *enc, CVPixelBufferRef *buf)
{
	OSStatus code;
	CVPixelBufferPoolRef pool =
		VTCompressionSessionGetPixelBufferPool(enc->session);
	if (!pool)
		return kCVReturnError;

	CVPixelBufferRef pixbuf;
	STATUS_CHECK(CVPixelBufferPoolCreatePixelBuffer(NULL, pool, &pixbuf));

	// Why aren't these already set on the pixel buffer?
	// I would have expected pixel buffers from the session's
	// pool to have the correct color space stuff set

	CFStringRef matrix = obs_to_vt_colorspace(enc->colorspace);

	CVBufferSetAttachment(pixbuf, kCVImageBufferYCbCrMatrixKey, matrix,
			      kCVAttachmentMode_ShouldPropagate);
	CVBufferSetAttachment(pixbuf, kCVImageBufferColorPrimariesKey,
			      kCVImageBufferColorPrimaries_ITU_R_709_2,
			      kCVAttachmentMode_ShouldPropagate);
	CVBufferSetAttachment(pixbuf, kCVImageBufferTransferFunctionKey,
			      kCVImageBufferTransferFunction_ITU_R_709_2,
			      kCVAttachmentMode_ShouldPropagate);

	*buf = pixbuf;
	return true;

fail:
	return false;
}