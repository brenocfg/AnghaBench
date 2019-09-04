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
struct bfa_lps_s {int /*<<< orphan*/  qe; scalar_t__ lp_pid; int /*<<< orphan*/  bfa; } ;
struct bfa_lps_mod_s {int /*<<< orphan*/  lps_free_q; } ;

/* Variables and functions */
 struct bfa_lps_mod_s* BFA_LPS_MOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_lps_free(struct bfa_lps_s *lps)
{
	struct bfa_lps_mod_s	*mod = BFA_LPS_MOD(lps->bfa);

	lps->lp_pid = 0;
	list_del(&lps->qe);
	list_add_tail(&lps->qe, &mod->lps_free_q);
}