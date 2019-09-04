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
 scalar_t__ LEGACY ; 
 unsigned long LEGACY_BOOTING ; 
 unsigned long LEGACY_RUNNING ; 
 unsigned long LEGACY_SUSPEND ; 
 unsigned long WMAX_RUNNING ; 
 scalar_t__ interface ; 
 unsigned long lighting_control_state ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static ssize_t store_control_state(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	long unsigned int val;
	if (strcmp(buf, "booting\n") == 0)
		val = LEGACY_BOOTING;
	else if (strcmp(buf, "suspend\n") == 0)
		val = LEGACY_SUSPEND;
	else if (interface == LEGACY)
		val = LEGACY_RUNNING;
	else
		val = WMAX_RUNNING;
	lighting_control_state = val;
	pr_debug("alienware-wmi: updated control state to %d\n",
		 lighting_control_state);
	return count;
}