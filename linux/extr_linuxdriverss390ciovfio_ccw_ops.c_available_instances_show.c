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
struct vfio_ccw_private {int /*<<< orphan*/  avail; } ;
struct kobject {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct vfio_ccw_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t available_instances_show(struct kobject *kobj,
					struct device *dev, char *buf)
{
	struct vfio_ccw_private *private = dev_get_drvdata(dev);

	return sprintf(buf, "%d\n", atomic_read(&private->avail));
}