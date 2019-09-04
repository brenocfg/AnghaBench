#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bfa_iocfc_s {TYPE_2__* bfa; } ;
typedef  enum iocfc_event { ____Placeholder_iocfc_event } iocfc_event ;
struct TYPE_6__ {int /*<<< orphan*/  dis_hcb_qe; int /*<<< orphan*/  op_status; } ;
struct TYPE_7__ {TYPE_1__ iocfc; int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_OK ; 
#define  IOCFC_E_DISABLE 132 
#define  IOCFC_E_IOC_DISABLED 131 
#define  IOCFC_E_IOC_ENABLED 130 
#define  IOCFC_E_IOC_FAILED 129 
#define  IOCFC_E_STOP 128 
 int /*<<< orphan*/  bfa_cb_queue (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bfa_iocfc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_iocfc_disable_cb ; 
 int /*<<< orphan*/  bfa_iocfc_sm_dconf_read ; 
 int /*<<< orphan*/  bfa_iocfc_sm_stopped ; 
 int /*<<< orphan*/  bfa_iocfc_sm_stopping ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_2__*,int) ; 

__attribute__((used)) static void
bfa_iocfc_sm_init_failed(struct bfa_iocfc_s *iocfc, enum iocfc_event event)
{
	bfa_trc(iocfc->bfa, event);

	switch (event) {
	case IOCFC_E_STOP:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_stopping);
		break;
	case IOCFC_E_DISABLE:
		bfa_ioc_disable(&iocfc->bfa->ioc);
		break;
	case IOCFC_E_IOC_ENABLED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_dconf_read);
		break;
	case IOCFC_E_IOC_DISABLED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_stopped);
		iocfc->bfa->iocfc.op_status = BFA_STATUS_OK;
		bfa_cb_queue(iocfc->bfa, &iocfc->bfa->iocfc.dis_hcb_qe,
			     bfa_iocfc_disable_cb, iocfc->bfa);
		break;
	case IOCFC_E_IOC_FAILED:
		break;
	default:
		bfa_sm_fault(iocfc->bfa, event);
		break;
	}
}