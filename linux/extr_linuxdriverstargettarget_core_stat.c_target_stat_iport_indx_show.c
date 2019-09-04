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
struct se_session {int dummy; } ;
struct se_portal_group {TYPE_1__* se_tpg_tfo; } ;
struct se_node_acl {int /*<<< orphan*/  nacl_sess_lock; struct se_portal_group* se_tpg; struct se_session* nacl_sess; } ;
struct se_lun_acl {struct se_node_acl* se_lun_nacl; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int (* sess_get_index ) (struct se_session*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct se_lun_acl* iport_to_lacl (struct config_item*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (struct se_session*) ; 
 int stub2 (struct se_session*) ; 

__attribute__((used)) static ssize_t target_stat_iport_indx_show(struct config_item *item,
		char *page)
{
	struct se_lun_acl *lacl = iport_to_lacl(item);
	struct se_node_acl *nacl = lacl->se_lun_nacl;
	struct se_session *se_sess;
	struct se_portal_group *tpg;
	ssize_t ret;

	spin_lock_irq(&nacl->nacl_sess_lock);
	se_sess = nacl->nacl_sess;
	if (!se_sess) {
		spin_unlock_irq(&nacl->nacl_sess_lock);
		return -ENODEV;
	}

	tpg = nacl->se_tpg;
	/* scsiAttIntrPortIndex */
	ret = snprintf(page, PAGE_SIZE, "%u\n",
			tpg->se_tpg_tfo->sess_get_index(se_sess));
	spin_unlock_irq(&nacl->nacl_sess_lock);
	return ret;
}