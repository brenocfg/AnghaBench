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
struct TYPE_2__ {char* unit_serial; } ;
struct se_device {TYPE_1__ t10_wwn; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 struct se_device* to_stat_lu_dev (struct config_item*) ; 

__attribute__((used)) static ssize_t target_stat_lu_lu_name_show(struct config_item *item, char *page)
{
	struct se_device *dev = to_stat_lu_dev(item);

	/* scsiLuWwnName */
	return snprintf(page, PAGE_SIZE, "%s\n",
			(strlen(dev->t10_wwn.unit_serial)) ?
			dev->t10_wwn.unit_serial : "None");
}