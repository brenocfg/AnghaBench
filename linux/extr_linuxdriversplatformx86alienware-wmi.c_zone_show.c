#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int red; int green; int blue; } ;
struct platform_zone {TYPE_1__ colors; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct platform_zone* match_zone (struct device_attribute*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t zone_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct platform_zone *target_zone;
	target_zone = match_zone(attr);
	if (target_zone == NULL)
		return sprintf(buf, "red: -1, green: -1, blue: -1\n");
	return sprintf(buf, "red: %d, green: %d, blue: %d\n",
		       target_zone->colors.red,
		       target_zone->colors.green, target_zone->colors.blue);

}