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
struct v4l2_input {int index; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  name; scalar_t__ std; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SKEL_TVNORMS ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_IN_CAP_DV_TIMINGS ; 
 int /*<<< orphan*/  V4L2_IN_CAP_STD ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int skeleton_enum_input(struct file *file, void *priv,
			       struct v4l2_input *i)
{
	if (i->index > 1)
		return -EINVAL;

	i->type = V4L2_INPUT_TYPE_CAMERA;
	if (i->index == 0) {
		i->std = SKEL_TVNORMS;
		strlcpy(i->name, "S-Video", sizeof(i->name));
		i->capabilities = V4L2_IN_CAP_STD;
	} else {
		i->std = 0;
		strlcpy(i->name, "HDMI", sizeof(i->name));
		i->capabilities = V4L2_IN_CAP_DV_TIMINGS;
	}
	return 0;
}