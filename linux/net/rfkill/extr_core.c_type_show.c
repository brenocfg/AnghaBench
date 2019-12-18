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
struct rfkill {size_t type; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char** rfkill_types ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct rfkill* to_rfkill (struct device*) ; 

__attribute__((used)) static ssize_t type_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct rfkill *rfkill = to_rfkill(dev);

	return sprintf(buf, "%s\n", rfkill_types[rfkill->type]);
}