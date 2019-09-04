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
 int /*<<< orphan*/  IOCPF_E_STOP ; 
#define  IOC_E_DETACH 132 
#define  IOC_E_DISABLE 131 
#define  IOC_E_ENABLE 130 
#define  IOC_E_HWERROR 129 
#define  IOC_E_HWFAILED 128 
 int /*<<< orphan*/  bfa_fsm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_sm_disabling ; 
 int /*<<< orphan*/  bfa_ioc_sm_uninit ; 
 int /*<<< orphan*/  bfa_sm_fault (struct bfa_ioc_s*,int) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_ioc_s*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_sm_fail(struct bfa_ioc_s *ioc, enum ioc_event event)
{
	bfa_trc(ioc, event);

	switch (event) {

	case IOC_E_ENABLE:
		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		break;

	case IOC_E_DISABLE:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_disabling);
		break;

	case IOC_E_DETACH:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_uninit);
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_STOP);
		break;

	case IOC_E_HWERROR:
	case IOC_E_HWFAILED:
		/*
		 * HB failure / HW error notification, ignore.
		 */
		break;
	default:
		bfa_sm_fault(ioc, event);
	}
}