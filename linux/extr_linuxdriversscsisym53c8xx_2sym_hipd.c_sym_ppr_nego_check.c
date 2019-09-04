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
struct TYPE_2__ {unsigned char period; unsigned char offset; unsigned char width; int check_nego; scalar_t__ qas; scalar_t__ dt; scalar_t__ iu; } ;
struct sym_tcb {TYPE_1__ tgoal; } ;
struct sym_hcb {unsigned char* msgin; unsigned char maxwide; int features; unsigned char maxoffs_dt; unsigned char maxoffs; unsigned char minsync_dt; unsigned char minsync; unsigned char* msgout; struct sym_tcb* target; } ;

/* Variables and functions */
 int DEBUG_FLAGS ; 
 int DEBUG_NEGO ; 
 int FE_U3EN ; 
 unsigned char M_NOOP ; 
 unsigned char PPR_OPT_DT ; 
 unsigned char PPR_OPT_MASK ; 
 int /*<<< orphan*/  spi_populate_ppr_msg (unsigned char*,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 scalar_t__ sym_getsync (struct sym_hcb*,int,unsigned char,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  sym_print_nego_msg (struct sym_hcb*,int,char*,unsigned char*) ; 
 int /*<<< orphan*/  sym_setpprot (struct sym_hcb*,int,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static int 
sym_ppr_nego_check(struct sym_hcb *np, int req, int target)
{
	struct sym_tcb *tp = &np->target[target];
	unsigned char fak, div;
	int dt, chg = 0;

	unsigned char per = np->msgin[3];
	unsigned char ofs = np->msgin[5];
	unsigned char wide = np->msgin[6];
	unsigned char opts = np->msgin[7] & PPR_OPT_MASK;

	if (DEBUG_FLAGS & DEBUG_NEGO) {
		sym_print_nego_msg(np, target, "ppr msgin", np->msgin);
	}

	/*
	 *  Check values against our limits.
	 */
	if (wide > np->maxwide) {
		chg = 1;
		wide = np->maxwide;
	}
	if (!wide || !(np->features & FE_U3EN))
		opts = 0;

	if (opts != (np->msgin[7] & PPR_OPT_MASK))
		chg = 1;

	dt = opts & PPR_OPT_DT;

	if (ofs) {
		unsigned char maxoffs = dt ? np->maxoffs_dt : np->maxoffs;
		if (ofs > maxoffs) {
			chg = 1;
			ofs = maxoffs;
		}
	}

	if (ofs) {
		unsigned char minsync = dt ? np->minsync_dt : np->minsync;
		if (per < minsync) {
			chg = 1;
			per = minsync;
		}
	}

	/*
	 *  Get new chip synchronous parameters value.
	 */
	div = fak = 0;
	if (ofs && sym_getsync(np, dt, per, &div, &fak) < 0)
		goto reject_it;

	/*
	 *  If it was an answer we want to change, 
	 *  then it isn't acceptable. Reject it.
	 */
	if (!req && chg)
		goto reject_it;

	/*
	 *  Apply new values.
	 */
	sym_setpprot(np, target, opts, ofs, per, wide, div, fak);

	/*
	 *  It was an answer. We are done.
	 */
	if (!req)
		return 0;

	/*
	 *  It was a request. Prepare an answer message.
	 */
	spi_populate_ppr_msg(np->msgout, per, ofs, wide, opts);

	if (DEBUG_FLAGS & DEBUG_NEGO) {
		sym_print_nego_msg(np, target, "ppr msgout", np->msgout);
	}

	np->msgin [0] = M_NOOP;

	return 0;

reject_it:
	sym_setpprot (np, target, 0, 0, 0, 0, 0, 0);
	/*
	 *  If it is a device response that should result in  
	 *  ST, we may want to try a legacy negotiation later.
	 */
	if (!req && !opts) {
		tp->tgoal.period = per;
		tp->tgoal.offset = ofs;
		tp->tgoal.width = wide;
		tp->tgoal.iu = tp->tgoal.dt = tp->tgoal.qas = 0;
		tp->tgoal.check_nego = 1;
	}
	return -1;
}