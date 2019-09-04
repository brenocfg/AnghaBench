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
struct nd_region {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int nd_region_to_nstype (struct nd_region*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct nd_region* to_nd_region (struct device*) ; 

__attribute__((used)) static ssize_t nstype_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nd_region *nd_region = to_nd_region(dev);

	return sprintf(buf, "%d\n", nd_region_to_nstype(nd_region));
}