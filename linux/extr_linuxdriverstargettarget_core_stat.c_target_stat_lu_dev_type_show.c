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
struct se_device {TYPE_1__* transport; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int (* get_device_type ) (struct se_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct se_device*) ; 
 int stub2 (struct se_device*) ; 
 struct se_device* to_stat_lu_dev (struct config_item*) ; 

__attribute__((used)) static ssize_t target_stat_lu_dev_type_show(struct config_item *item, char *page)
{
	struct se_device *dev = to_stat_lu_dev(item);

	/* scsiLuPeripheralType */
	return snprintf(page, PAGE_SIZE, "%u\n",
			dev->transport->get_device_type(dev));
}