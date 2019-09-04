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
struct TYPE_2__ {int /*<<< orphan*/  cg_item; } ;
struct t10_alua_tg_pt_gp {int tg_pt_gp_trans_delay_msecs; int /*<<< orphan*/  tg_pt_gp_id; TYPE_1__ tg_pt_gp_group; } ;
struct se_lun {scalar_t__ lun_tg_pt_secondary_write_md; int /*<<< orphan*/  lun_tg_pt_gp_lock; int /*<<< orphan*/  lun_tg_pt_secondary_stat; int /*<<< orphan*/  lun_tg_pt_secondary_offline; struct t10_alua_tg_pt_gp* lun_tg_pt_gp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALUA_STATUS_ALTERED_BY_EXPLICIT_STPG ; 
 int /*<<< orphan*/  ALUA_STATUS_ALTERED_BY_IMPLICIT_ALUA ; 
 int EINVAL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  config_item_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  core_alua_update_tpg_secondary_metadata (struct se_lun*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int core_alua_set_tg_pt_secondary_state(
	struct se_lun *lun,
	int explicit,
	int offline)
{
	struct t10_alua_tg_pt_gp *tg_pt_gp;
	int trans_delay_msecs;

	spin_lock(&lun->lun_tg_pt_gp_lock);
	tg_pt_gp = lun->lun_tg_pt_gp;
	if (!tg_pt_gp) {
		spin_unlock(&lun->lun_tg_pt_gp_lock);
		pr_err("Unable to complete secondary state"
				" transition\n");
		return -EINVAL;
	}
	trans_delay_msecs = tg_pt_gp->tg_pt_gp_trans_delay_msecs;
	/*
	 * Set the secondary ALUA target port access state to OFFLINE
	 * or release the previously secondary state for struct se_lun
	 */
	if (offline)
		atomic_set(&lun->lun_tg_pt_secondary_offline, 1);
	else
		atomic_set(&lun->lun_tg_pt_secondary_offline, 0);

	lun->lun_tg_pt_secondary_stat = (explicit) ?
			ALUA_STATUS_ALTERED_BY_EXPLICIT_STPG :
			ALUA_STATUS_ALTERED_BY_IMPLICIT_ALUA;

	pr_debug("Successful %s ALUA transition TG PT Group: %s ID: %hu"
		" to secondary access state: %s\n", (explicit) ? "explicit" :
		"implicit", config_item_name(&tg_pt_gp->tg_pt_gp_group.cg_item),
		tg_pt_gp->tg_pt_gp_id, (offline) ? "OFFLINE" : "ONLINE");

	spin_unlock(&lun->lun_tg_pt_gp_lock);
	/*
	 * Do the optional transition delay after we set the secondary
	 * ALUA access state.
	 */
	if (trans_delay_msecs != 0)
		msleep_interruptible(trans_delay_msecs);
	/*
	 * See if we need to update the ALUA fabric port metadata for
	 * secondary state and status
	 */
	if (lun->lun_tg_pt_secondary_write_md)
		core_alua_update_tpg_secondary_metadata(lun);

	return 0;
}