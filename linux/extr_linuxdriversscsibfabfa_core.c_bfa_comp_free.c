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
struct list_head {int dummy; } ;
struct bfa_s {int dummy; } ;
struct bfa_cb_qe_s {int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pre_rmv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_q_deq (struct list_head*,struct list_head**) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_comp_free(struct bfa_s *bfa, struct list_head *comp_q)
{
	struct list_head		*qe;
	struct bfa_cb_qe_s	*hcb_qe;

	while (!list_empty(comp_q)) {
		bfa_q_deq(comp_q, &qe);
		hcb_qe = (struct bfa_cb_qe_s *) qe;
		WARN_ON(hcb_qe->pre_rmv);
		hcb_qe->cbfn(hcb_qe->cbarg, BFA_FALSE);
	}
}