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
struct miscdevice {int dummy; } ;
struct kmod_test_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct miscdevice* dev_to_misc_dev (struct device*) ; 
 struct kmod_test_device* misc_dev_to_test_dev (struct miscdevice*) ; 

__attribute__((used)) static struct kmod_test_device *dev_to_test_dev(struct device *dev)
{
	struct miscdevice *misc_dev;

	misc_dev = dev_to_misc_dev(dev);

	return misc_dev_to_test_dev(misc_dev);
}