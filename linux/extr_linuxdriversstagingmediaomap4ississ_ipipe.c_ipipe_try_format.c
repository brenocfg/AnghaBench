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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {unsigned int width; unsigned int height; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; } ;
struct iss_ipipe_device {int dummy; } ;
typedef  enum v4l2_subdev_format_whence { ____Placeholder_v4l2_subdev_format_whence } v4l2_subdev_format_whence ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
#define  IPIPE_PAD_SINK 129 
#define  IPIPE_PAD_SOURCE_VP 128 
 int /*<<< orphan*/  MEDIA_BUS_FMT_SGRBG10_1X10 ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_UYVY8_1X16 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct v4l2_mbus_framefmt* __ipipe_get_format (struct iss_ipipe_device*,struct v4l2_subdev_pad_config*,int const,int) ; 
 void* clamp_t (int /*<<< orphan*/ ,unsigned int,int,int) ; 
 int /*<<< orphan*/ * ipipe_fmts ; 
 int /*<<< orphan*/  memcpy (struct v4l2_mbus_framefmt*,struct v4l2_mbus_framefmt*,int) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void
ipipe_try_format(struct iss_ipipe_device *ipipe,
		 struct v4l2_subdev_pad_config *cfg,
		 unsigned int pad,
		 struct v4l2_mbus_framefmt *fmt,
		 enum v4l2_subdev_format_whence which)
{
	struct v4l2_mbus_framefmt *format;
	unsigned int width = fmt->width;
	unsigned int height = fmt->height;
	unsigned int i;

	switch (pad) {
	case IPIPE_PAD_SINK:
		for (i = 0; i < ARRAY_SIZE(ipipe_fmts); i++) {
			if (fmt->code == ipipe_fmts[i])
				break;
		}

		/* If not found, use SGRBG10 as default */
		if (i >= ARRAY_SIZE(ipipe_fmts))
			fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;

		/* Clamp the input size. */
		fmt->width = clamp_t(u32, width, 1, 8192);
		fmt->height = clamp_t(u32, height, 1, 8192);
		fmt->colorspace = V4L2_COLORSPACE_SRGB;
		break;

	case IPIPE_PAD_SOURCE_VP:
		format = __ipipe_get_format(ipipe, cfg, IPIPE_PAD_SINK, which);
		memcpy(fmt, format, sizeof(*fmt));

		fmt->code = MEDIA_BUS_FMT_UYVY8_1X16;
		fmt->width = clamp_t(u32, width, 32, fmt->width);
		fmt->height = clamp_t(u32, height, 32, fmt->height);
		fmt->colorspace = V4L2_COLORSPACE_JPEG;
		break;
	}

	fmt->field = V4L2_FIELD_NONE;
}