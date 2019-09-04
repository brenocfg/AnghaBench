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
struct v4l2_subdev {struct list_head* host_priv; } ;
struct list_head {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct list_head *
to_pad_vdev_list(struct v4l2_subdev *sd, int pad_index)
{
	struct list_head *vdev_list = sd->host_priv;

	return vdev_list ? &vdev_list[pad_index] : NULL;
}