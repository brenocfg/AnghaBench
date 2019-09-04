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
struct bfa_itnim_s {int /*<<< orphan*/  pending_q; } ;
struct bfa_ioim_s {TYPE_1__* fcpim; int /*<<< orphan*/  qe; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioim_comp_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  bfa_ioim_tov (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_itnim_delayed_comp (struct bfa_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct bfa_ioim_s**) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_itnim_iotov_cleanup(struct bfa_itnim_s *itnim)
{
	struct bfa_ioim_s *ioim;

	/*
	 * Fail all inflight IO requests in the queue
	 */
	bfa_itnim_delayed_comp(itnim, BFA_TRUE);

	/*
	 * Fail any pending IO requests.
	 */
	while (!list_empty(&itnim->pending_q)) {
		bfa_q_deq(&itnim->pending_q, &ioim);
		list_add_tail(&ioim->qe, &ioim->fcpim->ioim_comp_q);
		bfa_ioim_tov(ioim);
	}
}