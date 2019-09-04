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
struct v4l2_queryctrl {scalar_t__ id; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct v4l2_queryctrl*) ; 
 int EINVAL ; 
 struct v4l2_queryctrl* bcm2048_v4l2_queryctrl ; 

__attribute__((used)) static int bcm2048_vidioc_queryctrl(struct file *file, void *priv,
				    struct v4l2_queryctrl *qc)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(bcm2048_v4l2_queryctrl); i++) {
		if (qc->id && qc->id == bcm2048_v4l2_queryctrl[i].id) {
			*qc = bcm2048_v4l2_queryctrl[i];
			return 0;
		}
	}

	return -EINVAL;
}