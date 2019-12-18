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
struct vfio_irq_info {scalar_t__ count; } ;
struct mdev_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int mbochs_get_irq_info(struct mdev_device *mdev,
			       struct vfio_irq_info *irq_info)
{
	irq_info->count = 0;
	return 0;
}