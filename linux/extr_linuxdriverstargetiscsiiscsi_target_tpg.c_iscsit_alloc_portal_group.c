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
typedef  int /*<<< orphan*/  u16 ;
struct iscsi_tiqn {int dummy; } ;
struct iscsi_portal_group {int /*<<< orphan*/  tpg_np_lock; int /*<<< orphan*/  tpg_state_lock; int /*<<< orphan*/  np_login_sem; int /*<<< orphan*/  tpg_access_lock; int /*<<< orphan*/  tpg_list; int /*<<< orphan*/  tpg_gnp_list; struct iscsi_tiqn* tpg_tiqn; int /*<<< orphan*/  tpg_state; int /*<<< orphan*/  tpgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TPG_STATE_FREE ; 
 struct iscsi_portal_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct iscsi_portal_group *iscsit_alloc_portal_group(struct iscsi_tiqn *tiqn, u16 tpgt)
{
	struct iscsi_portal_group *tpg;

	tpg = kzalloc(sizeof(struct iscsi_portal_group), GFP_KERNEL);
	if (!tpg) {
		pr_err("Unable to allocate struct iscsi_portal_group\n");
		return NULL;
	}

	tpg->tpgt = tpgt;
	tpg->tpg_state = TPG_STATE_FREE;
	tpg->tpg_tiqn = tiqn;
	INIT_LIST_HEAD(&tpg->tpg_gnp_list);
	INIT_LIST_HEAD(&tpg->tpg_list);
	mutex_init(&tpg->tpg_access_lock);
	sema_init(&tpg->np_login_sem, 1);
	spin_lock_init(&tpg->tpg_state_lock);
	spin_lock_init(&tpg->tpg_np_lock);

	return tpg;
}