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
struct config_item {int dummy; } ;
typedef  unsigned int ssize_t ;
struct TYPE_2__ {char* hr_dev_name; scalar_t__ hr_bdev; } ;

/* Variables and functions */
 unsigned int sprintf (char*,char*,char*) ; 
 TYPE_1__* to_o2hb_region (struct config_item*) ; 

__attribute__((used)) static ssize_t o2hb_region_dev_show(struct config_item *item, char *page)
{
	unsigned int ret = 0;

	if (to_o2hb_region(item)->hr_bdev)
		ret = sprintf(page, "%s\n", to_o2hb_region(item)->hr_dev_name);

	return ret;
}