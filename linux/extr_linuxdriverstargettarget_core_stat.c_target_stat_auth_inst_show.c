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
struct se_portal_group {TYPE_1__* se_tpg_tfo; } ;
struct se_node_acl {struct se_portal_group* se_tpg; } ;
struct se_lun_acl {int /*<<< orphan*/  mapped_lun; struct se_node_acl* se_lun_nacl; } ;
struct se_dev_entry {int dummy; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int (* tpg_get_inst_index ) (struct se_portal_group*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct se_lun_acl* auth_to_lacl (struct config_item*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct se_portal_group*) ; 
 int stub2 (struct se_portal_group*) ; 
 struct se_dev_entry* target_nacl_find_deve (struct se_node_acl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t target_stat_auth_inst_show(struct config_item *item,
		char *page)
{
	struct se_lun_acl *lacl = auth_to_lacl(item);
	struct se_node_acl *nacl = lacl->se_lun_nacl;
	struct se_dev_entry *deve;
	struct se_portal_group *tpg;
	ssize_t ret;

	rcu_read_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	if (!deve) {
		rcu_read_unlock();
		return -ENODEV;
	}
	tpg = nacl->se_tpg;
	/* scsiInstIndex */
	ret = snprintf(page, PAGE_SIZE, "%u\n",
			tpg->se_tpg_tfo->tpg_get_inst_index(tpg));
	rcu_read_unlock();
	return ret;
}