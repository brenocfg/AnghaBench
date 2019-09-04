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
struct bfa_sgpg_wqe_s {int nsgpg_total; int nsgpg; int /*<<< orphan*/  qe; int /*<<< orphan*/  sgpg_q; } ;
struct bfa_sgpg_mod_s {int free_sgpgs; int /*<<< orphan*/  sgpg_wait_q; int /*<<< orphan*/  sgpg_q; } ;
struct bfa_s {int dummy; } ;

/* Variables and functions */
 struct bfa_sgpg_mod_s* BFA_SGPG_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bfa_sgpg_wait(struct bfa_s *bfa, struct bfa_sgpg_wqe_s *wqe, int nsgpg)
{
	struct bfa_sgpg_mod_s *mod = BFA_SGPG_MOD(bfa);

	WARN_ON(nsgpg <= 0);
	WARN_ON(nsgpg <= mod->free_sgpgs);

	wqe->nsgpg_total = wqe->nsgpg = nsgpg;

	/*
	 * allocate any left to this one first
	 */
	if (mod->free_sgpgs) {
		/*
		 * no one else is waiting for SGPG
		 */
		WARN_ON(!list_empty(&mod->sgpg_wait_q));
		list_splice_tail_init(&mod->sgpg_q, &wqe->sgpg_q);
		wqe->nsgpg -= mod->free_sgpgs;
		mod->free_sgpgs = 0;
	}

	list_add_tail(&wqe->qe, &mod->sgpg_wait_q);
}