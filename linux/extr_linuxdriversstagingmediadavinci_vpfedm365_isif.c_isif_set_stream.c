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
struct vpfe_isif_device {scalar_t__ output; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ ISIF_OUTPUT_MEMORY ; 
 int isif_configure (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  isif_enable (struct vpfe_isif_device*,int) ; 
 int /*<<< orphan*/  isif_enable_output_to_sdram (struct vpfe_isif_device*,int) ; 
 struct vpfe_isif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int isif_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct vpfe_isif_device *isif = v4l2_get_subdevdata(sd);
	int ret;

	if (enable) {
		ret = isif_configure(sd,
			(isif->output == ISIF_OUTPUT_MEMORY) ? 0 : 1);
		if (ret)
			return ret;
		if (isif->output == ISIF_OUTPUT_MEMORY)
			isif_enable_output_to_sdram(isif, 1);
		isif_enable(isif, 1);
	} else {
		isif_enable(isif, 0);
		isif_enable_output_to_sdram(isif, 0);
	}

	return 0;
}