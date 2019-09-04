#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct otg_fsm {int state_changed; int id; int /*<<< orphan*/  lock; int /*<<< orphan*/  a_clr_err; int /*<<< orphan*/  a_bus_drop; int /*<<< orphan*/  a_wait_vfall_tmout; int /*<<< orphan*/  a_vbus_vld; int /*<<< orphan*/  b_bus_suspend; int /*<<< orphan*/  a_bidl_adis_tmout; int /*<<< orphan*/  a_aidl_bdis_tmout; int /*<<< orphan*/  b_bus_resume; int /*<<< orphan*/  a_bus_req; TYPE_3__* otg; int /*<<< orphan*/  b_conn; int /*<<< orphan*/  a_suspend_req_inf; int /*<<< orphan*/  a_wait_bcon_tmout; int /*<<< orphan*/  a_wait_vrise_tmout; int /*<<< orphan*/  power_up; int /*<<< orphan*/  adp_change; int /*<<< orphan*/  a_srp_det; int /*<<< orphan*/  test_device; int /*<<< orphan*/  a_conn; int /*<<< orphan*/  b_bus_req; int /*<<< orphan*/  b_sess_vld; int /*<<< orphan*/  b_ase0_brst_tmout; int /*<<< orphan*/  a_bus_resume; int /*<<< orphan*/  a_bus_suspend; int /*<<< orphan*/  b_srp_done; int /*<<< orphan*/  b_se0_srp; int /*<<< orphan*/  b_ssend_srp; } ;
typedef  enum usb_otg_state { ____Placeholder_usb_otg_state } usb_otg_state ;
struct TYPE_6__ {int state; TYPE_2__* host; TYPE_1__* gadget; } ;
struct TYPE_5__ {int /*<<< orphan*/  b_hnp_enable; } ;
struct TYPE_4__ {int /*<<< orphan*/  b_hnp_enable; } ;

/* Variables and functions */
#define  OTG_STATE_A_HOST 141 
#define  OTG_STATE_A_IDLE 140 
#define  OTG_STATE_A_PERIPHERAL 139 
#define  OTG_STATE_A_SUSPEND 138 
#define  OTG_STATE_A_VBUS_ERR 137 
#define  OTG_STATE_A_WAIT_BCON 136 
#define  OTG_STATE_A_WAIT_VFALL 135 
#define  OTG_STATE_A_WAIT_VRISE 134 
#define  OTG_STATE_B_HOST 133 
#define  OTG_STATE_B_IDLE 132 
#define  OTG_STATE_B_PERIPHERAL 131 
#define  OTG_STATE_B_SRP_INIT 130 
#define  OTG_STATE_B_WAIT_ACON 129 
#define  OTG_STATE_UNDEFINED 128 
 int /*<<< orphan*/  VDBG (char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  otg_set_state (struct otg_fsm*,int const) ; 

int otg_statemachine(struct otg_fsm *fsm)
{
	enum usb_otg_state state;

	mutex_lock(&fsm->lock);

	state = fsm->otg->state;
	fsm->state_changed = 0;
	/* State machine state change judgement */

	switch (state) {
	case OTG_STATE_UNDEFINED:
		VDBG("fsm->id = %d\n", fsm->id);
		if (fsm->id)
			otg_set_state(fsm, OTG_STATE_B_IDLE);
		else
			otg_set_state(fsm, OTG_STATE_A_IDLE);
		break;
	case OTG_STATE_B_IDLE:
		if (!fsm->id)
			otg_set_state(fsm, OTG_STATE_A_IDLE);
		else if (fsm->b_sess_vld && fsm->otg->gadget)
			otg_set_state(fsm, OTG_STATE_B_PERIPHERAL);
		else if ((fsm->b_bus_req || fsm->adp_change || fsm->power_up) &&
				fsm->b_ssend_srp && fsm->b_se0_srp)
			otg_set_state(fsm, OTG_STATE_B_SRP_INIT);
		break;
	case OTG_STATE_B_SRP_INIT:
		if (!fsm->id || fsm->b_srp_done)
			otg_set_state(fsm, OTG_STATE_B_IDLE);
		break;
	case OTG_STATE_B_PERIPHERAL:
		if (!fsm->id || !fsm->b_sess_vld)
			otg_set_state(fsm, OTG_STATE_B_IDLE);
		else if (fsm->b_bus_req && fsm->otg->
				gadget->b_hnp_enable && fsm->a_bus_suspend)
			otg_set_state(fsm, OTG_STATE_B_WAIT_ACON);
		break;
	case OTG_STATE_B_WAIT_ACON:
		if (fsm->a_conn)
			otg_set_state(fsm, OTG_STATE_B_HOST);
		else if (!fsm->id || !fsm->b_sess_vld)
			otg_set_state(fsm, OTG_STATE_B_IDLE);
		else if (fsm->a_bus_resume || fsm->b_ase0_brst_tmout) {
			fsm->b_ase0_brst_tmout = 0;
			otg_set_state(fsm, OTG_STATE_B_PERIPHERAL);
		}
		break;
	case OTG_STATE_B_HOST:
		if (!fsm->id || !fsm->b_sess_vld)
			otg_set_state(fsm, OTG_STATE_B_IDLE);
		else if (!fsm->b_bus_req || !fsm->a_conn || fsm->test_device)
			otg_set_state(fsm, OTG_STATE_B_PERIPHERAL);
		break;
	case OTG_STATE_A_IDLE:
		if (fsm->id)
			otg_set_state(fsm, OTG_STATE_B_IDLE);
		else if (!fsm->a_bus_drop && (fsm->a_bus_req ||
			  fsm->a_srp_det || fsm->adp_change || fsm->power_up))
			otg_set_state(fsm, OTG_STATE_A_WAIT_VRISE);
		break;
	case OTG_STATE_A_WAIT_VRISE:
		if (fsm->a_vbus_vld)
			otg_set_state(fsm, OTG_STATE_A_WAIT_BCON);
		else if (fsm->id || fsm->a_bus_drop ||
				fsm->a_wait_vrise_tmout)
			otg_set_state(fsm, OTG_STATE_A_WAIT_VFALL);
		break;
	case OTG_STATE_A_WAIT_BCON:
		if (!fsm->a_vbus_vld)
			otg_set_state(fsm, OTG_STATE_A_VBUS_ERR);
		else if (fsm->b_conn)
			otg_set_state(fsm, OTG_STATE_A_HOST);
		else if (fsm->id || fsm->a_bus_drop || fsm->a_wait_bcon_tmout)
			otg_set_state(fsm, OTG_STATE_A_WAIT_VFALL);
		break;
	case OTG_STATE_A_HOST:
		if (fsm->id || fsm->a_bus_drop)
			otg_set_state(fsm, OTG_STATE_A_WAIT_VFALL);
		else if ((!fsm->a_bus_req || fsm->a_suspend_req_inf) &&
				fsm->otg->host->b_hnp_enable)
			otg_set_state(fsm, OTG_STATE_A_SUSPEND);
		else if (!fsm->b_conn)
			otg_set_state(fsm, OTG_STATE_A_WAIT_BCON);
		else if (!fsm->a_vbus_vld)
			otg_set_state(fsm, OTG_STATE_A_VBUS_ERR);
		break;
	case OTG_STATE_A_SUSPEND:
		if (!fsm->b_conn && fsm->otg->host->b_hnp_enable)
			otg_set_state(fsm, OTG_STATE_A_PERIPHERAL);
		else if (!fsm->b_conn && !fsm->otg->host->b_hnp_enable)
			otg_set_state(fsm, OTG_STATE_A_WAIT_BCON);
		else if (fsm->a_bus_req || fsm->b_bus_resume)
			otg_set_state(fsm, OTG_STATE_A_HOST);
		else if (fsm->id || fsm->a_bus_drop || fsm->a_aidl_bdis_tmout)
			otg_set_state(fsm, OTG_STATE_A_WAIT_VFALL);
		else if (!fsm->a_vbus_vld)
			otg_set_state(fsm, OTG_STATE_A_VBUS_ERR);
		break;
	case OTG_STATE_A_PERIPHERAL:
		if (fsm->id || fsm->a_bus_drop)
			otg_set_state(fsm, OTG_STATE_A_WAIT_VFALL);
		else if (fsm->a_bidl_adis_tmout || fsm->b_bus_suspend)
			otg_set_state(fsm, OTG_STATE_A_WAIT_BCON);
		else if (!fsm->a_vbus_vld)
			otg_set_state(fsm, OTG_STATE_A_VBUS_ERR);
		break;
	case OTG_STATE_A_WAIT_VFALL:
		if (fsm->a_wait_vfall_tmout)
			otg_set_state(fsm, OTG_STATE_A_IDLE);
		break;
	case OTG_STATE_A_VBUS_ERR:
		if (fsm->id || fsm->a_bus_drop || fsm->a_clr_err)
			otg_set_state(fsm, OTG_STATE_A_WAIT_VFALL);
		break;
	default:
		break;
	}
	mutex_unlock(&fsm->lock);

	VDBG("quit statemachine, changed = %d\n", fsm->state_changed);
	return fsm->state_changed;
}