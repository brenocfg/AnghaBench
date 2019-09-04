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
struct vfio_container {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct vfio_container* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfio_container_put (struct vfio_container*) ; 

__attribute__((used)) static int vfio_fops_release(struct inode *inode, struct file *filep)
{
	struct vfio_container *container = filep->private_data;

	filep->private_data = NULL;

	vfio_container_put(container);

	return 0;
}