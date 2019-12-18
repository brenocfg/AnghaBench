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
struct tc_cbq_lssopt {int change; int flags; int /*<<< orphan*/  offtime; int /*<<< orphan*/  maxidle; scalar_t__ minidle; int /*<<< orphan*/  avpkt; int /*<<< orphan*/  ewma_log; } ;
struct cbq_class {long minidle; int /*<<< orphan*/  offtime; int /*<<< orphan*/  avgidle; int /*<<< orphan*/  maxidle; int /*<<< orphan*/  avpkt; int /*<<< orphan*/  ewma_log; int /*<<< orphan*/ * tparent; int /*<<< orphan*/ * borrow; int /*<<< orphan*/ * share; } ;

/* Variables and functions */
 int TCF_CBQ_LSS_AVPKT ; 
 int TCF_CBQ_LSS_BOUNDED ; 
 int TCF_CBQ_LSS_EWMA ; 
 int TCF_CBQ_LSS_FLAGS ; 
 int TCF_CBQ_LSS_ISOLATED ; 
 int TCF_CBQ_LSS_MAXIDLE ; 
 int TCF_CBQ_LSS_MINIDLE ; 
 int TCF_CBQ_LSS_OFFTIME ; 

__attribute__((used)) static int cbq_set_lss(struct cbq_class *cl, struct tc_cbq_lssopt *lss)
{
	if (lss->change & TCF_CBQ_LSS_FLAGS) {
		cl->share = (lss->flags & TCF_CBQ_LSS_ISOLATED) ? NULL : cl->tparent;
		cl->borrow = (lss->flags & TCF_CBQ_LSS_BOUNDED) ? NULL : cl->tparent;
	}
	if (lss->change & TCF_CBQ_LSS_EWMA)
		cl->ewma_log = lss->ewma_log;
	if (lss->change & TCF_CBQ_LSS_AVPKT)
		cl->avpkt = lss->avpkt;
	if (lss->change & TCF_CBQ_LSS_MINIDLE)
		cl->minidle = -(long)lss->minidle;
	if (lss->change & TCF_CBQ_LSS_MAXIDLE) {
		cl->maxidle = lss->maxidle;
		cl->avgidle = lss->maxidle;
	}
	if (lss->change & TCF_CBQ_LSS_OFFTIME)
		cl->offtime = lss->offtime;
	return 0;
}