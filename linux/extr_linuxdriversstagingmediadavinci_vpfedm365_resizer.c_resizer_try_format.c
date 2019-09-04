#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct TYPE_6__ {struct v4l2_subdev subdev; } ;
struct TYPE_5__ {struct v4l2_subdev subdev; } ;
struct TYPE_4__ {struct v4l2_subdev subdev; } ;
struct vpfe_resizer_device {TYPE_3__ resizer_b; TYPE_2__ resizer_a; TYPE_1__ crop_resizer; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; int width; int height; } ;
typedef  enum v4l2_subdev_format_whence { ____Placeholder_v4l2_subdev_format_whence } v4l2_subdev_format_whence ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 unsigned int IPIPE_MAX_OUTPUT_HEIGHT_A ; 
 unsigned int IPIPE_MAX_OUTPUT_HEIGHT_B ; 
 unsigned int IPIPE_MAX_OUTPUT_WIDTH_A ; 
 unsigned int IPIPE_MAX_OUTPUT_WIDTH_B ; 
 unsigned int MAX_IN_HEIGHT ; 
 unsigned int MAX_IN_WIDTH ; 
 void* MEDIA_BUS_FMT_UYVY8_2X8 ; 
 int /*<<< orphan*/  MIN_IN_HEIGHT ; 
 int /*<<< orphan*/  MIN_IN_WIDTH ; 
 int /*<<< orphan*/  MIN_OUT_HEIGHT ; 
 int /*<<< orphan*/  MIN_OUT_WIDTH ; 
 unsigned int RESIZER_CROP_PAD_SINK ; 
 unsigned int RESIZER_CROP_PAD_SOURCE ; 
 unsigned int RESIZER_CROP_PAD_SOURCE2 ; 
 unsigned int RESIZER_PAD_SINK ; 
 unsigned int RESIZER_PAD_SOURCE ; 
 void* clamp_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__* resizer_input_formats ; 
 scalar_t__* resizer_output_formats ; 
 int /*<<< orphan*/  u32 ; 
 struct vpfe_resizer_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static void
resizer_try_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
	unsigned int pad, struct v4l2_mbus_framefmt *fmt,
	enum v4l2_subdev_format_whence which)
{
	struct vpfe_resizer_device *resizer = v4l2_get_subdevdata(sd);
	unsigned int max_out_height;
	unsigned int max_out_width;
	unsigned int i;

	if ((&resizer->resizer_a.subdev == sd && pad == RESIZER_PAD_SINK) ||
	    (&resizer->resizer_b.subdev == sd && pad == RESIZER_PAD_SINK) ||
	    (&resizer->crop_resizer.subdev == sd &&
	    (pad == RESIZER_CROP_PAD_SOURCE ||
	    pad == RESIZER_CROP_PAD_SOURCE2 || pad == RESIZER_CROP_PAD_SINK))) {
		for (i = 0; i < ARRAY_SIZE(resizer_input_formats); i++) {
			if (fmt->code == resizer_input_formats[i])
				break;
		}
		/* If not found, use UYVY as default */
		if (i >= ARRAY_SIZE(resizer_input_formats))
			fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;

		fmt->width = clamp_t(u32, fmt->width, MIN_IN_WIDTH,
					MAX_IN_WIDTH);
		fmt->height = clamp_t(u32, fmt->height, MIN_IN_HEIGHT,
				MAX_IN_HEIGHT);
	} else if (&resizer->resizer_a.subdev == sd &&
		   pad == RESIZER_PAD_SOURCE) {
		max_out_width = IPIPE_MAX_OUTPUT_WIDTH_A;
		max_out_height = IPIPE_MAX_OUTPUT_HEIGHT_A;

		for (i = 0; i < ARRAY_SIZE(resizer_output_formats); i++) {
			if (fmt->code == resizer_output_formats[i])
				break;
		}
		/* If not found, use UYVY as default */
		if (i >= ARRAY_SIZE(resizer_output_formats))
			fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;

		fmt->width = clamp_t(u32, fmt->width, MIN_OUT_WIDTH,
					max_out_width);
		fmt->width &= ~15;
		fmt->height = clamp_t(u32, fmt->height, MIN_OUT_HEIGHT,
				max_out_height);
	} else if (&resizer->resizer_b.subdev == sd &&
		   pad == RESIZER_PAD_SOURCE) {
		max_out_width = IPIPE_MAX_OUTPUT_WIDTH_B;
		max_out_height = IPIPE_MAX_OUTPUT_HEIGHT_B;

		for (i = 0; i < ARRAY_SIZE(resizer_output_formats); i++) {
			if (fmt->code == resizer_output_formats[i])
				break;
		}
		/* If not found, use UYVY as default */
		if (i >= ARRAY_SIZE(resizer_output_formats))
			fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;

		fmt->width = clamp_t(u32, fmt->width, MIN_OUT_WIDTH,
					max_out_width);
		fmt->width &= ~15;
		fmt->height = clamp_t(u32, fmt->height, MIN_OUT_HEIGHT,
				max_out_height);
	}
}