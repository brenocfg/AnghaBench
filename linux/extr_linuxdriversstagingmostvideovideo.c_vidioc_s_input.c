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
struct most_video_dev {unsigned int ctrl_input; } ;
struct file {int dummy; } ;
struct comp_fh {struct most_video_dev* mdev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int V4L2_CMP_MAX_INPUT ; 

__attribute__((used)) static int vidioc_s_input(struct file *file, void *priv, unsigned int index)
{
	struct comp_fh *fh = priv;
	struct most_video_dev *mdev = fh->mdev;

	if (index >= V4L2_CMP_MAX_INPUT)
		return -EINVAL;
	mdev->ctrl_input = index;
	return 0;
}