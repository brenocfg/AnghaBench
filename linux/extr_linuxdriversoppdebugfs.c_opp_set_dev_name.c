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
struct device {struct device const* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_MAX ; 
 char* dev_name (struct device const*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,...) ; 

__attribute__((used)) static void opp_set_dev_name(const struct device *dev, char *name)
{
	if (dev->parent)
		snprintf(name, NAME_MAX, "%s-%s", dev_name(dev->parent),
			 dev_name(dev));
	else
		snprintf(name, NAME_MAX, "%s", dev_name(dev));
}