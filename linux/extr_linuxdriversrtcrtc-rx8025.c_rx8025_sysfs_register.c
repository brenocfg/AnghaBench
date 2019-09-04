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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_clock_adjust_ppb ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rx8025_sysfs_register(struct device *dev)
{
	return device_create_file(dev, &dev_attr_clock_adjust_ppb);
}