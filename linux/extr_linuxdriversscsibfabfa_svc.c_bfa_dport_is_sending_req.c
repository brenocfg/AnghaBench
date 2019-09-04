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
struct bfa_dport_s {int dummy; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  bfa_dport_sm_disabling ; 
 int /*<<< orphan*/  bfa_dport_sm_disabling_qwait ; 
 int /*<<< orphan*/  bfa_dport_sm_enabling ; 
 int /*<<< orphan*/  bfa_dport_sm_enabling_qwait ; 
 int /*<<< orphan*/  bfa_dport_sm_starting ; 
 int /*<<< orphan*/  bfa_dport_sm_starting_qwait ; 
 scalar_t__ bfa_sm_cmp_state (struct bfa_dport_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfa_boolean_t
bfa_dport_is_sending_req(struct bfa_dport_s *dport)
{
	if (bfa_sm_cmp_state(dport, bfa_dport_sm_enabling)	||
	    bfa_sm_cmp_state(dport, bfa_dport_sm_enabling_qwait) ||
	    bfa_sm_cmp_state(dport, bfa_dport_sm_disabling)	||
	    bfa_sm_cmp_state(dport, bfa_dport_sm_disabling_qwait) ||
	    bfa_sm_cmp_state(dport, bfa_dport_sm_starting)	||
	    bfa_sm_cmp_state(dport, bfa_dport_sm_starting_qwait)) {
		return BFA_TRUE;
	} else {
		return BFA_FALSE;
	}
}