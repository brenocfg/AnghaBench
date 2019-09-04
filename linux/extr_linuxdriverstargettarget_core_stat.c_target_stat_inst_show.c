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
struct se_hba {int hba_index; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {struct se_hba* se_hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* to_stat_dev (struct config_item*) ; 

__attribute__((used)) static ssize_t target_stat_inst_show(struct config_item *item, char *page)
{
	struct se_hba *hba = to_stat_dev(item)->se_hba;

	return snprintf(page, PAGE_SIZE, "%u\n", hba->hba_index);
}