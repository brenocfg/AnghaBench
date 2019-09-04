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
struct char_device_struct {scalar_t__ cdev; } ;

/* Variables and functions */
 struct char_device_struct* __unregister_chrdev_region (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  cdev_del (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct char_device_struct*) ; 

void __unregister_chrdev(unsigned int major, unsigned int baseminor,
			 unsigned int count, const char *name)
{
	struct char_device_struct *cd;

	cd = __unregister_chrdev_region(major, baseminor, count);
	if (cd && cd->cdev)
		cdev_del(cd->cdev);
	kfree(cd);
}