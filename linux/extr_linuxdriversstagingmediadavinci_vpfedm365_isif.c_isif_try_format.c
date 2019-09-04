#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vpfe_isif_device {int dummy; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct TYPE_2__ {unsigned int width; unsigned int height; scalar_t__ code; } ;
struct v4l2_subdev_format {scalar_t__ pad; TYPE_1__ format; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ ISIF_PAD_SOURCE ; 
 int /*<<< orphan*/  MAX_HEIGHT ; 
 int /*<<< orphan*/  MAX_WIDTH ; 
 scalar_t__ MEDIA_BUS_FMT_YUYV8_2X8 ; 
 void* clamp_t (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__* isif_fmts ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void
isif_try_format(struct vpfe_isif_device *isif,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *fmt)
{
	unsigned int width = fmt->format.width;
	unsigned int height = fmt->format.height;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(isif_fmts); i++) {
		if (fmt->format.code == isif_fmts[i])
			break;
	}

	/* If not found, use YUYV8_2x8 as default */
	if (i >= ARRAY_SIZE(isif_fmts))
		fmt->format.code = MEDIA_BUS_FMT_YUYV8_2X8;

	/* Clamp the size. */
	fmt->format.width = clamp_t(u32, width, 32, MAX_WIDTH);
	fmt->format.height = clamp_t(u32, height, 32, MAX_HEIGHT);

	/* The data formatter truncates the number of horizontal output
	 * pixels to a multiple of 16. To avoid clipping data, allow
	 * callers to request an output size bigger than the input size
	 * up to the nearest multiple of 16.
	 */
	if (fmt->pad == ISIF_PAD_SOURCE)
		fmt->format.width &= ~15;
}