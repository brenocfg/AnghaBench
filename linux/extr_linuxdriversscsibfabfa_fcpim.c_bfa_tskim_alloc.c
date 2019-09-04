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
struct bfad_tskim_s {int dummy; } ;
struct bfa_tskim_s {struct bfad_tskim_s* dtsk; } ;
struct bfa_s {int dummy; } ;
struct bfa_fcpim_s {int /*<<< orphan*/  tskim_free_q; } ;

/* Variables and functions */
 struct bfa_fcpim_s* BFA_FCPIM (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct bfa_tskim_s**) ; 

struct bfa_tskim_s *
bfa_tskim_alloc(struct bfa_s *bfa, struct bfad_tskim_s *dtsk)
{
	struct bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	struct bfa_tskim_s *tskim;

	bfa_q_deq(&fcpim->tskim_free_q, &tskim);

	if (tskim)
		tskim->dtsk = dtsk;

	return tskim;
}