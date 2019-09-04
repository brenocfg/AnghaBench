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
typedef  int /*<<< orphan*/  uint32_t ;
struct bfa_lps_s {int /*<<< orphan*/  lp_pid; int /*<<< orphan*/  bfa; int /*<<< orphan*/  bfa_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_LPS_SM_SET_N2N_PID ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_lps_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_lps_set_n2n_pid(struct bfa_lps_s *lps, uint32_t n2n_pid)
{
	bfa_trc(lps->bfa, lps->bfa_tag);
	bfa_trc(lps->bfa, n2n_pid);

	lps->lp_pid = n2n_pid;
	bfa_sm_send_event(lps, BFA_LPS_SM_SET_N2N_PID);
}