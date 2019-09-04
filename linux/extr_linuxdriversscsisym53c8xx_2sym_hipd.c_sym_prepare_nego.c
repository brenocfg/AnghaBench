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
typedef  int /*<<< orphan*/  u_char ;
struct sym_trans {int renego; int period; scalar_t__ qas; scalar_t__ dt; scalar_t__ iu; scalar_t__ width; scalar_t__ offset; scalar_t__ check_nego; } ;
struct sym_tcb {struct sym_ccb* nego_cp; struct sym_trans tgoal; struct scsi_target* starget; } ;
struct sym_hcb {struct sym_tcb* target; } ;
struct sym_ccb {size_t target; int nego_status; } ;
struct scsi_target {int dummy; } ;

/* Variables and functions */
 int DEBUG_FLAGS ; 
 int DEBUG_NEGO ; 
#define  NS_PPR 130 
#define  NS_SYNC 129 
#define  NS_WIDE 128 
 int PPR_OPT_DT ; 
 int PPR_OPT_IU ; 
 int PPR_OPT_QAS ; 
 int spi_populate_ppr_msg (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,int) ; 
 int spi_populate_sync_msg (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int spi_populate_width_msg (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sym_check_goals (struct sym_hcb*,struct scsi_target*,struct sym_trans*) ; 
 int /*<<< orphan*/  sym_print_nego_msg (struct sym_hcb*,size_t,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sym_prepare_nego(struct sym_hcb *np, struct sym_ccb *cp, u_char *msgptr)
{
	struct sym_tcb *tp = &np->target[cp->target];
	struct scsi_target *starget = tp->starget;
	struct sym_trans *goal = &tp->tgoal;
	int msglen = 0;
	int nego;

	sym_check_goals(np, starget, goal);

	/*
	 * Many devices implement PPR in a buggy way, so only use it if we
	 * really want to.
	 */
	if (goal->renego == NS_PPR || (goal->offset &&
	    (goal->iu || goal->dt || goal->qas || (goal->period < 0xa)))) {
		nego = NS_PPR;
	} else if (goal->renego == NS_WIDE || goal->width) {
		nego = NS_WIDE;
	} else if (goal->renego == NS_SYNC || goal->offset) {
		nego = NS_SYNC;
	} else {
		goal->check_nego = 0;
		nego = 0;
	}

	switch (nego) {
	case NS_SYNC:
		msglen += spi_populate_sync_msg(msgptr + msglen, goal->period,
				goal->offset);
		break;
	case NS_WIDE:
		msglen += spi_populate_width_msg(msgptr + msglen, goal->width);
		break;
	case NS_PPR:
		msglen += spi_populate_ppr_msg(msgptr + msglen, goal->period,
				goal->offset, goal->width,
				(goal->iu ? PPR_OPT_IU : 0) |
					(goal->dt ? PPR_OPT_DT : 0) |
					(goal->qas ? PPR_OPT_QAS : 0));
		break;
	}

	cp->nego_status = nego;

	if (nego) {
		tp->nego_cp = cp; /* Keep track a nego will be performed */
		if (DEBUG_FLAGS & DEBUG_NEGO) {
			sym_print_nego_msg(np, cp->target, 
					  nego == NS_SYNC ? "sync msgout" :
					  nego == NS_WIDE ? "wide msgout" :
					  "ppr msgout", msgptr);
		}
	}

	return msglen;
}