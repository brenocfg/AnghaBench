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
struct se_device {int /*<<< orphan*/  num_cmds; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct se_device* to_stat_lu_dev (struct config_item*) ; 

__attribute__((used)) static ssize_t target_stat_lu_num_cmds_show(struct config_item *item,
		char *page)
{
	struct se_device *dev = to_stat_lu_dev(item);

	/* scsiLuNumCommands */
	return snprintf(page, PAGE_SIZE, "%lu\n",
			atomic_long_read(&dev->num_cmds));
}