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
struct se_session {int /*<<< orphan*/  se_node_acl; } ;
struct se_dev_entry {scalar_t__ lun_access_ro; } ;
struct se_cmd {int /*<<< orphan*/  orig_fe_lun; struct se_session* se_sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct se_dev_entry* target_nacl_find_deve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool target_lun_is_rdonly(struct se_cmd *cmd)
{
	struct se_session *se_sess = cmd->se_sess;
	struct se_dev_entry *deve;
	bool ret;

	rcu_read_lock();
	deve = target_nacl_find_deve(se_sess->se_node_acl, cmd->orig_fe_lun);
	ret = deve && deve->lun_access_ro;
	rcu_read_unlock();

	return ret;
}