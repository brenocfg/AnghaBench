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
struct nd_region {struct device dev; } ;

/* Variables and functions */

struct device *nd_region_dev(struct nd_region *nd_region)
{
	if (!nd_region)
		return NULL;
	return &nd_region->dev;
}