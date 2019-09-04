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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {scalar_t__ export_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* to_stat_tgt_dev (struct config_item*) ; 

__attribute__((used)) static ssize_t target_stat_tgt_non_access_lus_show(struct config_item *item,
		char *page)
{
	int non_accessible_lus;

	if (to_stat_tgt_dev(item)->export_count)
		non_accessible_lus = 0;
	else
		non_accessible_lus = 1;

	return snprintf(page, PAGE_SIZE, "%u\n", non_accessible_lus);
}