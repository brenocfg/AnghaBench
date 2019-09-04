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
struct bfa_s {int /*<<< orphan*/  iocfc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCFC_E_INIT ; 
 int /*<<< orphan*/  bfa_fsm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
bfa_iocfc_init(struct bfa_s *bfa)
{
	bfa_fsm_send_event(&bfa->iocfc, IOCFC_E_INIT);
}