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
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int rx8025_set_clock_adjust (struct device*,int) ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static ssize_t rx8025_sysfs_store_clock_adjust(struct device *dev,
					       struct device_attribute *attr,
					       const char *buf, size_t count)
{
	int adj, err;

	if (sscanf(buf, "%i", &adj) != 1)
		return -EINVAL;

	err = rx8025_set_clock_adjust(dev, adj);

	return err ? err : count;
}