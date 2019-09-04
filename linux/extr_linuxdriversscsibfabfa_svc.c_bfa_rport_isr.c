#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
union bfi_rport_i2h_msg_u {TYPE_5__* lip_scn; TYPE_4__* qos_scn_evt; TYPE_2__* delete_rsp; TYPE_1__* create_rsp; struct bfi_msg_s* msg; } ;
struct TYPE_12__ {int msg_id; } ;
struct bfi_msg_s {TYPE_6__ mhdr; } ;
struct bfa_s {int dummy; } ;
struct TYPE_9__ {TYPE_4__* fw_msg; } ;
struct bfa_rport_s {int /*<<< orphan*/  rport_drv; TYPE_3__ event_arg; int /*<<< orphan*/  qos_attr; int /*<<< orphan*/  fw_handle; } ;
struct TYPE_11__ {int /*<<< orphan*/  bfa_handle; int /*<<< orphan*/  loop_info; } ;
struct TYPE_10__ {int /*<<< orphan*/  bfa_handle; } ;
struct TYPE_8__ {int /*<<< orphan*/  status; int /*<<< orphan*/  bfa_handle; } ;
struct TYPE_7__ {int /*<<< orphan*/  status; int /*<<< orphan*/  qos_attr; int /*<<< orphan*/  fw_handle; int /*<<< orphan*/  bfa_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCPORT_MOD (struct bfa_s*) ; 
 struct bfa_rport_s* BFA_RPORT_FROM_TAG (struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BFA_RPORT_SM_FWRSP ; 
 int /*<<< orphan*/  BFA_RPORT_SM_QOS_SCN ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
#define  BFI_RPORT_I2H_CREATE_RSP 133 
#define  BFI_RPORT_I2H_DELETE_RSP 132 
#define  BFI_RPORT_I2H_LIP_SCN_OFFLINE 131 
#define  BFI_RPORT_I2H_LIP_SCN_ONLINE 130 
#define  BFI_RPORT_I2H_NO_DEV 129 
#define  BFI_RPORT_I2H_QOS_SCN 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_cb_rport_scn_no_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_cb_rport_scn_offline (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_cb_rport_scn_online (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_fcport_update_loop_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_rport_set_lunmask (struct bfa_s*,struct bfa_rport_s*) ; 
 int /*<<< orphan*/  bfa_rport_unset_lunmask (struct bfa_s*,struct bfa_rport_s*) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int) ; 

void
bfa_rport_isr(struct bfa_s *bfa, struct bfi_msg_s *m)
{
	union bfi_rport_i2h_msg_u msg;
	struct bfa_rport_s *rp;

	bfa_trc(bfa, m->mhdr.msg_id);

	msg.msg = m;

	switch (m->mhdr.msg_id) {
	case BFI_RPORT_I2H_CREATE_RSP:
		rp = BFA_RPORT_FROM_TAG(bfa, msg.create_rsp->bfa_handle);
		rp->fw_handle = msg.create_rsp->fw_handle;
		rp->qos_attr = msg.create_rsp->qos_attr;
		bfa_rport_set_lunmask(bfa, rp);
		WARN_ON(msg.create_rsp->status != BFA_STATUS_OK);
		bfa_sm_send_event(rp, BFA_RPORT_SM_FWRSP);
		break;

	case BFI_RPORT_I2H_DELETE_RSP:
		rp = BFA_RPORT_FROM_TAG(bfa, msg.delete_rsp->bfa_handle);
		WARN_ON(msg.delete_rsp->status != BFA_STATUS_OK);
		bfa_rport_unset_lunmask(bfa, rp);
		bfa_sm_send_event(rp, BFA_RPORT_SM_FWRSP);
		break;

	case BFI_RPORT_I2H_QOS_SCN:
		rp = BFA_RPORT_FROM_TAG(bfa, msg.qos_scn_evt->bfa_handle);
		rp->event_arg.fw_msg = msg.qos_scn_evt;
		bfa_sm_send_event(rp, BFA_RPORT_SM_QOS_SCN);
		break;

	case BFI_RPORT_I2H_LIP_SCN_ONLINE:
		bfa_fcport_update_loop_info(BFA_FCPORT_MOD(bfa),
				&msg.lip_scn->loop_info);
		bfa_cb_rport_scn_online(bfa);
		break;

	case BFI_RPORT_I2H_LIP_SCN_OFFLINE:
		bfa_cb_rport_scn_offline(bfa);
		break;

	case BFI_RPORT_I2H_NO_DEV:
		rp = BFA_RPORT_FROM_TAG(bfa, msg.lip_scn->bfa_handle);
		bfa_cb_rport_scn_no_dev(rp->rport_drv);
		break;

	default:
		bfa_trc(bfa, m->mhdr.msg_id);
		WARN_ON(1);
	}
}