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
struct se_lun {int /*<<< orphan*/  lun_se_dev; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  core_alua_show_offline_bit (struct se_lun*,char*) ; 
 struct se_lun* item_to_lun (struct config_item*) ; 

__attribute__((used)) static ssize_t target_fabric_port_alua_tg_pt_offline_show(
		struct config_item *item, char *page)
{
	struct se_lun *lun = item_to_lun(item);

	if (!lun || !lun->lun_se_dev)
		return -ENODEV;

	return core_alua_show_offline_bit(lun, page);
}