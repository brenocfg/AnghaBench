#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfa_ioim_s {int /*<<< orphan*/  sgpg_q; int /*<<< orphan*/  sgpg; TYPE_2__* iosp; int /*<<< orphan*/  nsges; int /*<<< orphan*/  nsgpgs; } ;
struct TYPE_3__ {int /*<<< orphan*/  sgpg_q; } ;
struct TYPE_4__ {TYPE_1__ sgpg_wqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_IOIM_SM_SGALLOCED ; 
 int /*<<< orphan*/  BFA_SGPG_NPAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_q_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_ioim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_ioim_sgpg_alloced(void *cbarg)
{
	struct bfa_ioim_s *ioim = cbarg;

	ioim->nsgpgs = BFA_SGPG_NPAGE(ioim->nsges);
	list_splice_tail_init(&ioim->iosp->sgpg_wqe.sgpg_q, &ioim->sgpg_q);
	ioim->sgpg = bfa_q_first(&ioim->sgpg_q);
	bfa_sm_send_event(ioim, BFA_IOIM_SM_SGALLOCED);
}