#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct t10_alua_tg_pt_gp {int tg_pt_gp_alua_access_state; int tg_pt_gp_nonop_delay_msecs; } ;
struct se_lun {int /*<<< orphan*/  lun_tg_pt_gp_lock; struct t10_alua_tg_pt_gp* lun_tg_pt_gp; int /*<<< orphan*/  lun_tg_pt_secondary_offline; } ;
struct se_device {TYPE_2__* transport; TYPE_1__* se_hba; } ;
struct se_cmd {unsigned char* t_task_cdb; struct se_lun* se_lun; struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_4__ {int transport_flags; } ;
struct TYPE_3__ {int hba_flags; } ;

/* Variables and functions */
#define  ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED 133 
 int ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED ; 
#define  ALUA_ACCESS_STATE_LBA_DEPENDENT 132 
#define  ALUA_ACCESS_STATE_OFFLINE 131 
#define  ALUA_ACCESS_STATE_STANDBY 130 
#define  ALUA_ACCESS_STATE_TRANSITION 129 
#define  ALUA_ACCESS_STATE_UNAVAILABLE 128 
 int /*<<< orphan*/  ASCQ_04H_ALUA_OFFLINE ; 
 int HBA_FLAGS_INTERNAL_USE ; 
 int /*<<< orphan*/  TCM_CHECK_CONDITION_NOT_READY ; 
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int TRANSPORT_FLAG_PASSTHROUGH_ALUA ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  core_alua_state_lba_dependent (struct se_cmd*,struct t10_alua_tg_pt_gp*) ; 
 int /*<<< orphan*/  core_alua_state_nonoptimized (struct se_cmd*,unsigned char*,int) ; 
 int /*<<< orphan*/  core_alua_state_standby (struct se_cmd*,unsigned char*) ; 
 int /*<<< orphan*/  core_alua_state_transition (struct se_cmd*,unsigned char*) ; 
 int /*<<< orphan*/  core_alua_state_unavailable (struct se_cmd*,unsigned char*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  set_ascq (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

sense_reason_t
target_alua_state_check(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	unsigned char *cdb = cmd->t_task_cdb;
	struct se_lun *lun = cmd->se_lun;
	struct t10_alua_tg_pt_gp *tg_pt_gp;
	int out_alua_state, nonop_delay_msecs;

	if (dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE)
		return 0;
	if (dev->transport->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_ALUA)
		return 0;

	/*
	 * First, check for a struct se_port specific secondary ALUA target port
	 * access state: OFFLINE
	 */
	if (atomic_read(&lun->lun_tg_pt_secondary_offline)) {
		pr_debug("ALUA: Got secondary offline status for local"
				" target port\n");
		set_ascq(cmd, ASCQ_04H_ALUA_OFFLINE);
		return TCM_CHECK_CONDITION_NOT_READY;
	}

	if (!lun->lun_tg_pt_gp)
		return 0;

	spin_lock(&lun->lun_tg_pt_gp_lock);
	tg_pt_gp = lun->lun_tg_pt_gp;
	out_alua_state = tg_pt_gp->tg_pt_gp_alua_access_state;
	nonop_delay_msecs = tg_pt_gp->tg_pt_gp_nonop_delay_msecs;

	// XXX: keeps using tg_pt_gp witout reference after unlock
	spin_unlock(&lun->lun_tg_pt_gp_lock);
	/*
	 * Process ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED in a separate conditional
	 * statement so the compiler knows explicitly to check this case first.
	 * For the Optimized ALUA access state case, we want to process the
	 * incoming fabric cmd ASAP..
	 */
	if (out_alua_state == ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED)
		return 0;

	switch (out_alua_state) {
	case ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED:
		core_alua_state_nonoptimized(cmd, cdb, nonop_delay_msecs);
		break;
	case ALUA_ACCESS_STATE_STANDBY:
		if (core_alua_state_standby(cmd, cdb))
			return TCM_CHECK_CONDITION_NOT_READY;
		break;
	case ALUA_ACCESS_STATE_UNAVAILABLE:
		if (core_alua_state_unavailable(cmd, cdb))
			return TCM_CHECK_CONDITION_NOT_READY;
		break;
	case ALUA_ACCESS_STATE_TRANSITION:
		if (core_alua_state_transition(cmd, cdb))
			return TCM_CHECK_CONDITION_NOT_READY;
		break;
	case ALUA_ACCESS_STATE_LBA_DEPENDENT:
		if (core_alua_state_lba_dependent(cmd, tg_pt_gp))
			return TCM_CHECK_CONDITION_NOT_READY;
		break;
	/*
	 * OFFLINE is a secondary ALUA target port group access state, that is
	 * handled above with struct se_lun->lun_tg_pt_secondary_offline=1
	 */
	case ALUA_ACCESS_STATE_OFFLINE:
	default:
		pr_err("Unknown ALUA access state: 0x%02x\n",
				out_alua_state);
		return TCM_INVALID_CDB_FIELD;
	}

	return 0;
}