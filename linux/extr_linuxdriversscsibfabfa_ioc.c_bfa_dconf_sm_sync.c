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
struct bfa_dconf_mod_s {int /*<<< orphan*/  bfa; int /*<<< orphan*/  timer; } ;
typedef  enum bfa_dconf_event { ____Placeholder_bfa_dconf_event } bfa_dconf_event ;

/* Variables and functions */
#define  BFA_DCONF_SM_EXIT 131 
#define  BFA_DCONF_SM_FLASH_COMP 130 
#define  BFA_DCONF_SM_IOCDISABLE 129 
#define  BFA_DCONF_SM_WR 128 
 int /*<<< orphan*/  BFA_DCONF_UPDATE_TOV ; 
 int /*<<< orphan*/  bfa_dconf_sm_dirty ; 
 int /*<<< orphan*/  bfa_dconf_sm_final_sync ; 
 int /*<<< orphan*/  bfa_dconf_sm_iocdown_dirty ; 
 int /*<<< orphan*/  bfa_dconf_sm_ready ; 
 int /*<<< orphan*/  bfa_dconf_timer ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_dconf_mod_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_dconf_mod_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_dconf_sm_sync(struct bfa_dconf_mod_s *dconf, enum bfa_dconf_event event)
{
	bfa_trc(dconf->bfa, event);

	switch (event) {
	case BFA_DCONF_SM_FLASH_COMP:
		bfa_sm_set_state(dconf, bfa_dconf_sm_ready);
		break;
	case BFA_DCONF_SM_WR:
		bfa_timer_start(dconf->bfa, &dconf->timer,
			bfa_dconf_timer, dconf, BFA_DCONF_UPDATE_TOV);
		bfa_sm_set_state(dconf, bfa_dconf_sm_dirty);
		break;
	case BFA_DCONF_SM_EXIT:
		bfa_timer_start(dconf->bfa, &dconf->timer,
			bfa_dconf_timer, dconf, BFA_DCONF_UPDATE_TOV);
		bfa_sm_set_state(dconf, bfa_dconf_sm_final_sync);
		break;
	case BFA_DCONF_SM_IOCDISABLE:
		bfa_sm_set_state(dconf, bfa_dconf_sm_iocdown_dirty);
		break;
	default:
		bfa_sm_fault(dconf->bfa, event);
	}
}