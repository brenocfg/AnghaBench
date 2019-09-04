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
typedef  size_t u8 ;
struct platform_zone {int /*<<< orphan*/  location; scalar_t__ attr; } ;
struct device_attribute {int dummy; } ;
struct TYPE_2__ {size_t num_zones; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* quirks ; 
 struct platform_zone* zone_data ; 

__attribute__((used)) static struct platform_zone *match_zone(struct device_attribute *attr)
{
	u8 zone;

	for (zone = 0; zone < quirks->num_zones; zone++) {
		if ((struct device_attribute *)zone_data[zone].attr == attr) {
			pr_debug("alienware-wmi: matched zone location: %d\n",
				 zone_data[zone].location);
			return &zone_data[zone];
		}
	}
	return NULL;
}