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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long HZ ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 unsigned long lb_interval_jiffies ; 

__attribute__((used)) static ssize_t interval_msec_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	unsigned long msec;

	if (kstrtoul(buf, 0, &msec))
		return -EINVAL;

	lb_interval_jiffies = msec * HZ / 1000;

	return count;
}