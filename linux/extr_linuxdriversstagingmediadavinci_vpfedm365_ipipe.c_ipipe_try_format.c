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
struct vpfe_ipipe_device {int dummy; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; void* height; void* width; } ;
typedef  enum v4l2_subdev_format_whence { ____Placeholder_v4l2_subdev_format_whence } v4l2_subdev_format_whence ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 unsigned int IPIPE_MAX_OUTPUT_HEIGHT_A ; 
 unsigned int IPIPE_MAX_OUTPUT_WIDTH_A ; 
 unsigned int IPIPE_PAD_SINK ; 
 unsigned int IPIPE_PAD_SOURCE ; 
 scalar_t__ MEDIA_BUS_FMT_SGRBG12_1X12 ; 
 scalar_t__ MEDIA_BUS_FMT_UYVY8_2X8 ; 
 int /*<<< orphan*/  MIN_OUT_HEIGHT ; 
 int /*<<< orphan*/  MIN_OUT_WIDTH ; 
 void* clamp_t (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__* ipipe_input_fmts ; 
 scalar_t__* ipipe_output_fmts ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void
ipipe_try_format(struct vpfe_ipipe_device *ipipe,
		   struct v4l2_subdev_pad_config *cfg, unsigned int pad,
		   struct v4l2_mbus_framefmt *fmt,
		   enum v4l2_subdev_format_whence which)
{
	unsigned int max_out_height;
	unsigned int max_out_width;
	unsigned int i;

	max_out_width = IPIPE_MAX_OUTPUT_WIDTH_A;
	max_out_height = IPIPE_MAX_OUTPUT_HEIGHT_A;

	if (pad == IPIPE_PAD_SINK) {
		for (i = 0; i < ARRAY_SIZE(ipipe_input_fmts); i++)
			if (fmt->code == ipipe_input_fmts[i])
				break;

		/* If not found, use SBGGR10 as default */
		if (i >= ARRAY_SIZE(ipipe_input_fmts))
			fmt->code = MEDIA_BUS_FMT_SGRBG12_1X12;
	} else if (pad == IPIPE_PAD_SOURCE) {
		for (i = 0; i < ARRAY_SIZE(ipipe_output_fmts); i++)
			if (fmt->code == ipipe_output_fmts[i])
				break;

		/* If not found, use UYVY as default */
		if (i >= ARRAY_SIZE(ipipe_output_fmts))
			fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;
	}

	fmt->width = clamp_t(u32, fmt->width, MIN_OUT_HEIGHT, max_out_width);
	fmt->height = clamp_t(u32, fmt->height, MIN_OUT_WIDTH, max_out_height);
}