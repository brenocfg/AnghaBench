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
typedef  int /*<<< orphan*/  u16 ;
struct bfad_ioim_s {int dummy; } ;
struct bfa_s {int dummy; } ;
struct bfa_itnim_s {int /*<<< orphan*/  io_q; } ;
struct bfa_iotag_s {int /*<<< orphan*/  tag; } ;
struct bfa_ioim_s {int /*<<< orphan*/  qe; scalar_t__ nsgpgs; int /*<<< orphan*/  nsges; struct bfa_itnim_s* itnim; struct bfad_ioim_s* dio; } ;
struct bfa_fcpim_s {int /*<<< orphan*/  ios_active; TYPE_1__* fcp; } ;
struct TYPE_2__ {int /*<<< orphan*/  iotag_ioim_free_q; } ;

/* Variables and functions */
 struct bfa_fcpim_s* BFA_FCPIM (struct bfa_s*) ; 
 struct bfa_ioim_s* BFA_IOIM_FROM_TAG (struct bfa_fcpim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct bfa_iotag_s**) ; 
 int /*<<< orphan*/  bfa_stats (struct bfa_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  no_iotags ; 
 int /*<<< orphan*/  total_ios ; 

struct bfa_ioim_s *
bfa_ioim_alloc(struct bfa_s *bfa, struct bfad_ioim_s *dio,
		struct bfa_itnim_s *itnim, u16 nsges)
{
	struct bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	struct bfa_ioim_s *ioim;
	struct bfa_iotag_s *iotag = NULL;

	/*
	 * alocate IOIM resource
	 */
	bfa_q_deq(&fcpim->fcp->iotag_ioim_free_q, &iotag);
	if (!iotag) {
		bfa_stats(itnim, no_iotags);
		return NULL;
	}

	ioim = BFA_IOIM_FROM_TAG(fcpim, iotag->tag);

	ioim->dio = dio;
	ioim->itnim = itnim;
	ioim->nsges = nsges;
	ioim->nsgpgs = 0;

	bfa_stats(itnim, total_ios);
	fcpim->ios_active++;

	list_add_tail(&ioim->qe, &itnim->io_q);

	return ioim;
}