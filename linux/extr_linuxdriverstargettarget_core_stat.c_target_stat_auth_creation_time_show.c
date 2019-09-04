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
typedef  int u32 ;
struct se_node_acl {int dummy; } ;
struct se_lun_acl {int /*<<< orphan*/  mapped_lun; struct se_node_acl* se_lun_nacl; } ;
struct se_dev_entry {scalar_t__ creation_time; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int HZ ; 
 int INITIAL_JIFFIES ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct se_lun_acl* auth_to_lacl (struct config_item*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct se_dev_entry* target_nacl_find_deve (struct se_node_acl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t target_stat_auth_creation_time_show(struct config_item *item,
		char *page)
{
	struct se_lun_acl *lacl = auth_to_lacl(item);
	struct se_node_acl *nacl = lacl->se_lun_nacl;
	struct se_dev_entry *deve;
	ssize_t ret;

	rcu_read_lock();
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	if (!deve) {
		rcu_read_unlock();
		return -ENODEV;
	}
	/* scsiAuthIntrLastCreation */
	ret = snprintf(page, PAGE_SIZE, "%u\n", (u32)(((u32)deve->creation_time -
				INITIAL_JIFFIES) * 100 / HZ));
	rcu_read_unlock();
	return ret;
}