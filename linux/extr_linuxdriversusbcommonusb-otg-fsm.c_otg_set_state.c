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
struct otg_fsm {int state_changed; TYPE_1__* otg; int /*<<< orphan*/  a_suspend_req_inf; int /*<<< orphan*/  a_bus_req; int /*<<< orphan*/  a_bus_suspend; } ;
typedef  enum usb_otg_state { ____Placeholder_usb_otg_state } usb_otg_state ;
struct TYPE_4__ {int /*<<< orphan*/  otg_port; } ;
struct TYPE_3__ {int state; TYPE_2__* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_AIDL_BDIS ; 
 int /*<<< orphan*/  A_BIDL_ADIS ; 
 int /*<<< orphan*/  A_WAIT_BCON ; 
 int /*<<< orphan*/  A_WAIT_ENUM ; 
 int /*<<< orphan*/  A_WAIT_VFALL ; 
 int /*<<< orphan*/  A_WAIT_VRISE ; 
 int /*<<< orphan*/  B_ASE0_BRST ; 
 int /*<<< orphan*/  B_SE0_SRP ; 
 int /*<<< orphan*/  B_SRP_FAIL ; 
#define  OTG_STATE_A_HOST 140 
#define  OTG_STATE_A_IDLE 139 
#define  OTG_STATE_A_PERIPHERAL 138 
#define  OTG_STATE_A_SUSPEND 137 
#define  OTG_STATE_A_VBUS_ERR 136 
#define  OTG_STATE_A_WAIT_BCON 135 
#define  OTG_STATE_A_WAIT_VFALL 134 
#define  OTG_STATE_A_WAIT_VRISE 133 
#define  OTG_STATE_B_HOST 132 
#define  OTG_STATE_B_IDLE 131 
#define  OTG_STATE_B_PERIPHERAL 130 
#define  OTG_STATE_B_SRP_INIT 129 
#define  OTG_STATE_B_WAIT_ACON 128 
 int /*<<< orphan*/  PROTO_GADGET ; 
 int /*<<< orphan*/  PROTO_HOST ; 
 int /*<<< orphan*/  PROTO_UNDEF ; 
 int /*<<< orphan*/  VDBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_add_timer (struct otg_fsm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_chrg_vbus (struct otg_fsm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_drv_vbus (struct otg_fsm*,int) ; 
 int /*<<< orphan*/  otg_leave_state (struct otg_fsm*,int) ; 
 int /*<<< orphan*/  otg_loc_conn (struct otg_fsm*,int) ; 
 int /*<<< orphan*/  otg_loc_sof (struct otg_fsm*,int) ; 
 int /*<<< orphan*/  otg_set_protocol (struct otg_fsm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_start_adp_prb (struct otg_fsm*) ; 
 int /*<<< orphan*/  otg_start_adp_sns (struct otg_fsm*) ; 
 int /*<<< orphan*/  otg_start_hnp_polling (struct otg_fsm*) ; 
 int /*<<< orphan*/  otg_start_pulse (struct otg_fsm*) ; 
 int /*<<< orphan*/  usb_bus_start_enum (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_otg_state_string (int) ; 

__attribute__((used)) static int otg_set_state(struct otg_fsm *fsm, enum usb_otg_state new_state)
{
	if (fsm->otg->state == new_state)
		return 0;
	VDBG("Set state: %s\n", usb_otg_state_string(new_state));
	otg_leave_state(fsm, fsm->otg->state);
	switch (new_state) {
	case OTG_STATE_B_IDLE:
		otg_drv_vbus(fsm, 0);
		otg_chrg_vbus(fsm, 0);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		/*
		 * Driver is responsible for starting ADP probing
		 * if ADP sensing times out.
		 */
		otg_start_adp_sns(fsm);
		otg_set_protocol(fsm, PROTO_UNDEF);
		otg_add_timer(fsm, B_SE0_SRP);
		break;
	case OTG_STATE_B_SRP_INIT:
		otg_start_pulse(fsm);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_UNDEF);
		otg_add_timer(fsm, B_SRP_FAIL);
		break;
	case OTG_STATE_B_PERIPHERAL:
		otg_chrg_vbus(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_GADGET);
		otg_loc_conn(fsm, 1);
		break;
	case OTG_STATE_B_WAIT_ACON:
		otg_chrg_vbus(fsm, 0);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_HOST);
		otg_add_timer(fsm, B_ASE0_BRST);
		fsm->a_bus_suspend = 0;
		break;
	case OTG_STATE_B_HOST:
		otg_chrg_vbus(fsm, 0);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 1);
		otg_set_protocol(fsm, PROTO_HOST);
		usb_bus_start_enum(fsm->otg->host,
				fsm->otg->host->otg_port);
		otg_start_hnp_polling(fsm);
		break;
	case OTG_STATE_A_IDLE:
		otg_drv_vbus(fsm, 0);
		otg_chrg_vbus(fsm, 0);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_start_adp_prb(fsm);
		otg_set_protocol(fsm, PROTO_HOST);
		break;
	case OTG_STATE_A_WAIT_VRISE:
		otg_drv_vbus(fsm, 1);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_HOST);
		otg_add_timer(fsm, A_WAIT_VRISE);
		break;
	case OTG_STATE_A_WAIT_BCON:
		otg_drv_vbus(fsm, 1);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_HOST);
		otg_add_timer(fsm, A_WAIT_BCON);
		break;
	case OTG_STATE_A_HOST:
		otg_drv_vbus(fsm, 1);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 1);
		otg_set_protocol(fsm, PROTO_HOST);
		/*
		 * When HNP is triggered while a_bus_req = 0, a_host will
		 * suspend too fast to complete a_set_b_hnp_en
		 */
		if (!fsm->a_bus_req || fsm->a_suspend_req_inf)
			otg_add_timer(fsm, A_WAIT_ENUM);
		otg_start_hnp_polling(fsm);
		break;
	case OTG_STATE_A_SUSPEND:
		otg_drv_vbus(fsm, 1);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_HOST);
		otg_add_timer(fsm, A_AIDL_BDIS);

		break;
	case OTG_STATE_A_PERIPHERAL:
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_GADGET);
		otg_drv_vbus(fsm, 1);
		otg_loc_conn(fsm, 1);
		otg_add_timer(fsm, A_BIDL_ADIS);
		break;
	case OTG_STATE_A_WAIT_VFALL:
		otg_drv_vbus(fsm, 0);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_HOST);
		otg_add_timer(fsm, A_WAIT_VFALL);
		break;
	case OTG_STATE_A_VBUS_ERR:
		otg_drv_vbus(fsm, 0);
		otg_loc_conn(fsm, 0);
		otg_loc_sof(fsm, 0);
		otg_set_protocol(fsm, PROTO_UNDEF);
		break;
	default:
		break;
	}

	fsm->otg->state = new_state;
	fsm->state_changed = 1;
	return 0;
}