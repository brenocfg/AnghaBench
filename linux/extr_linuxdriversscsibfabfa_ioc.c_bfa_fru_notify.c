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
struct bfa_fru_s {int /*<<< orphan*/  op_busy; int /*<<< orphan*/  status; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  enum bfa_ioc_event_e { ____Placeholder_bfa_ioc_event_e } bfa_ioc_event_e ;

/* Variables and functions */
#define  BFA_IOC_E_DISABLED 129 
#define  BFA_IOC_E_FAILED 128 
 int /*<<< orphan*/  BFA_STATUS_IOC_FAILURE ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_fru_s*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fru_notify(void *cbarg, enum bfa_ioc_event_e event)
{
	struct bfa_fru_s *fru = cbarg;

	bfa_trc(fru, event);

	switch (event) {
	case BFA_IOC_E_DISABLED:
	case BFA_IOC_E_FAILED:
		if (fru->op_busy) {
			fru->status = BFA_STATUS_IOC_FAILURE;
			fru->cbfn(fru->cbarg, fru->status);
			fru->op_busy = 0;
		}
		break;

	default:
		break;
	}
}