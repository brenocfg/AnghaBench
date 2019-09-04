#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ output; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_3__ {struct v4l2_subdev subdev; } ;
struct vpfe_resizer_device {TYPE_2__ resizer_a; TYPE_1__ crop_resizer; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RESIZER_OUTPUT_MEMORY ; 
 int /*<<< orphan*/  resizer_do_hw_setup (struct vpfe_resizer_device*) ; 
 int /*<<< orphan*/  resizer_enable (struct vpfe_resizer_device*,int) ; 
 struct vpfe_resizer_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int resizer_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct vpfe_resizer_device *resizer = v4l2_get_subdevdata(sd);

	if (&resizer->crop_resizer.subdev != sd)
		return 0;

	if (resizer->resizer_a.output != RESIZER_OUTPUT_MEMORY)
		return 0;

	switch (enable) {
	case 1:
		if (resizer_do_hw_setup(resizer) < 0)
			return -EINVAL;
		resizer_enable(resizer, enable);
		break;

	case 0:
		resizer_enable(resizer, enable);
		break;
	}

	return 0;
}