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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
#define  AV_PIX_FMT_BGRA 134 
 int const AV_PIX_FMT_NONE ; 
#define  AV_PIX_FMT_NV12 133 
#define  AV_PIX_FMT_RGBA 132 
#define  AV_PIX_FMT_UYVY422 131 
#define  AV_PIX_FMT_YUV420P 130 
#define  AV_PIX_FMT_YUV444P 129 
#define  AV_PIX_FMT_YUYV422 128 
 int /*<<< orphan*/  bgra_formats ; 
 int get_best_format (int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  i420_formats ; 
 int /*<<< orphan*/  i444_formats ; 
 int /*<<< orphan*/  nv12_formats ; 
 int /*<<< orphan*/  rgba_formats ; 
 int /*<<< orphan*/  uyvy_formats ; 
 int /*<<< orphan*/  yuy2_formats ; 

__attribute__((used)) static inline enum AVPixelFormat get_closest_format(
		enum AVPixelFormat format,
		const enum AVPixelFormat *formats)
{
	enum AVPixelFormat best_format = AV_PIX_FMT_NONE;

	if (!formats || formats[0] == AV_PIX_FMT_NONE)
		return format;

	switch ((int)format) {

	case AV_PIX_FMT_YUV444P:
		best_format = get_best_format(i444_formats, formats);
		break;
	case AV_PIX_FMT_YUV420P:
		best_format = get_best_format(i420_formats, formats);
		break;
	case AV_PIX_FMT_NV12:
		best_format = get_best_format(nv12_formats, formats);
		break;
	case AV_PIX_FMT_YUYV422:
		best_format = get_best_format(yuy2_formats, formats);
		break;
	case AV_PIX_FMT_UYVY422:
		best_format = get_best_format(uyvy_formats, formats);
		break;
	case AV_PIX_FMT_RGBA:
		best_format = get_best_format(rgba_formats, formats);
		break;
	case AV_PIX_FMT_BGRA:
		best_format = get_best_format(bgra_formats, formats);
		break;
	}

	return (best_format == AV_PIX_FMT_NONE) ? formats[0] : best_format;
}