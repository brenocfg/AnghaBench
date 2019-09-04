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
struct vfio_group {int dummy; } ;
struct file {int /*<<< orphan*/ * f_op; struct vfio_group* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfio_group_fops ; 

bool vfio_external_group_match_file(struct vfio_group *test_group,
				    struct file *filep)
{
	struct vfio_group *group = filep->private_data;

	return (filep->f_op == &vfio_group_fops) && (group == test_group);
}