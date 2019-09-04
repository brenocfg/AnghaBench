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
struct iscsi_tiqn {int /*<<< orphan*/  tiqn_tpg_lock; int /*<<< orphan*/  tiqn; int /*<<< orphan*/  tiqn_ntpgs; int /*<<< orphan*/  tiqn_tpg_list; } ;
struct TYPE_2__ {struct iscsi_portal_group* tpg; } ;
struct iscsi_portal_group {scalar_t__ tpg_state; int /*<<< orphan*/ * param_list; int /*<<< orphan*/  tpgt; int /*<<< orphan*/  tpg_list; int /*<<< orphan*/  tpg_state_lock; TYPE_1__ tpg_attrib; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 scalar_t__ TPG_STATE_FREE ; 
 scalar_t__ TPG_STATE_INACTIVE ; 
 scalar_t__ iscsi_create_default_params (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  iscsi_release_param_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsit_set_default_tpg_attribs (struct iscsi_portal_group*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int iscsit_tpg_add_portal_group(struct iscsi_tiqn *tiqn, struct iscsi_portal_group *tpg)
{
	if (tpg->tpg_state != TPG_STATE_FREE) {
		pr_err("Unable to add iSCSI Target Portal Group: %d"
			" while not in TPG_STATE_FREE state.\n", tpg->tpgt);
		return -EEXIST;
	}
	iscsit_set_default_tpg_attribs(tpg);

	if (iscsi_create_default_params(&tpg->param_list) < 0)
		goto err_out;

	tpg->tpg_attrib.tpg = tpg;

	spin_lock(&tpg->tpg_state_lock);
	tpg->tpg_state	= TPG_STATE_INACTIVE;
	spin_unlock(&tpg->tpg_state_lock);

	spin_lock(&tiqn->tiqn_tpg_lock);
	list_add_tail(&tpg->tpg_list, &tiqn->tiqn_tpg_list);
	tiqn->tiqn_ntpgs++;
	pr_debug("CORE[%s]_TPG[%hu] - Added iSCSI Target Portal Group\n",
			tiqn->tiqn, tpg->tpgt);
	spin_unlock(&tiqn->tiqn_tpg_lock);

	return 0;
err_out:
	if (tpg->param_list) {
		iscsi_release_param_list(tpg->param_list);
		tpg->param_list = NULL;
	}
	return -ENOMEM;
}