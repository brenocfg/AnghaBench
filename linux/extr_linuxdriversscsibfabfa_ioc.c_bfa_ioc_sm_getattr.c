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
struct bfa_ioc_s {int /*<<< orphan*/  iocpf; int /*<<< orphan*/  bfa; TYPE_1__* cbfn; } ;
typedef  enum ioc_event { ____Placeholder_ioc_event } ioc_event ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_IOC_FAILURE ; 
 int /*<<< orphan*/  IOCPF_E_GETATTRFAIL ; 
#define  IOC_E_DISABLE 133 
#define  IOC_E_ENABLE 132 
#define  IOC_E_FWRSP_GETATTR 131 
#define  IOC_E_HWERROR 130 
#define  IOC_E_PFFAILED 129 
#define  IOC_E_TIMEOUT 128 
 int /*<<< orphan*/  bfa_fsm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_sm_disabling ; 
 int /*<<< orphan*/  bfa_ioc_sm_fail ; 
 int /*<<< orphan*/  bfa_ioc_sm_op ; 
 int /*<<< orphan*/  bfa_ioc_timer_stop (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_sm_fault (struct bfa_ioc_s*,int) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_ioc_s*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_sm_getattr(struct bfa_ioc_s *ioc, enum ioc_event event)
{
	bfa_trc(ioc, event);

	switch (event) {
	case IOC_E_FWRSP_GETATTR:
		bfa_ioc_timer_stop(ioc);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_op);
		break;

	case IOC_E_PFFAILED:
	case IOC_E_HWERROR:
		bfa_ioc_timer_stop(ioc);
		/* !!! fall through !!! */
	case IOC_E_TIMEOUT:
		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_fail);
		if (event != IOC_E_PFFAILED)
			bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_GETATTRFAIL);
		break;

	case IOC_E_DISABLE:
		bfa_ioc_timer_stop(ioc);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_disabling);
		break;

	case IOC_E_ENABLE:
		break;

	default:
		bfa_sm_fault(ioc, event);
	}
}