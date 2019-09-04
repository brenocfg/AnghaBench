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

/* Variables and functions */
 int /*<<< orphan*/  BFA_DPORT_SM_QRESUME ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_dport_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_dport_qresume(void *cbarg)
{
	struct bfa_dport_s *dport = cbarg;

	bfa_sm_send_event(dport, BFA_DPORT_SM_QRESUME);
}