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
struct vt_h264_encoder {scalar_t__ obs_pix_fmt; scalar_t__ fullrange; int /*<<< orphan*/  vt_pix_fmt; } ;
struct video_scale_info {scalar_t__ format; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ VIDEO_FORMAT_I420 ; 
 scalar_t__ VIDEO_FORMAT_I444 ; 
 scalar_t__ VIDEO_FORMAT_NV12 ; 
 int /*<<< orphan*/  VT_BLOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kCVPixelFormatType_420YpCbCr8BiPlanarFullRange ; 
 int /*<<< orphan*/  kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange ; 
 int /*<<< orphan*/  kCVPixelFormatType_420YpCbCr8Planar ; 
 int /*<<< orphan*/  kCVPixelFormatType_420YpCbCr8PlanarFullRange ; 

__attribute__((used)) static void vt_h264_video_info(void *data, struct video_scale_info *info)
{
	struct vt_h264_encoder *enc = data;

	if (info->format == VIDEO_FORMAT_I420) {
		enc->obs_pix_fmt = info->format;
		enc->vt_pix_fmt =
			enc->fullrange
				? kCVPixelFormatType_420YpCbCr8PlanarFullRange
				: kCVPixelFormatType_420YpCbCr8Planar;
		return;
	}

	if (info->format == VIDEO_FORMAT_I444)
		VT_BLOG(LOG_WARNING, "I444 color format not supported");

	// Anything else, return default
	enc->obs_pix_fmt = VIDEO_FORMAT_NV12;
	enc->vt_pix_fmt =
		enc->fullrange
			? kCVPixelFormatType_420YpCbCr8BiPlanarFullRange
			: kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange;

	info->format = enc->obs_pix_fmt;
}