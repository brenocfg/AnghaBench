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
typedef  scalar_t__ u32 ;
struct clgstate {int state; scalar_t__ a3; scalar_t__ a2; scalar_t__ a5; scalar_t__ a4; scalar_t__ a1; } ;
struct netem_sched_data {struct clgstate clg; } ;

/* Variables and functions */
#define  LOST_IN_BURST_PERIOD 131 
#define  LOST_IN_GAP_PERIOD 130 
#define  TX_IN_BURST_PERIOD 129 
#define  TX_IN_GAP_PERIOD 128 
 scalar_t__ prandom_u32 () ; 

__attribute__((used)) static bool loss_4state(struct netem_sched_data *q)
{
	struct clgstate *clg = &q->clg;
	u32 rnd = prandom_u32();

	/*
	 * Makes a comparison between rnd and the transition
	 * probabilities outgoing from the current state, then decides the
	 * next state and if the next packet has to be transmitted or lost.
	 * The four states correspond to:
	 *   TX_IN_GAP_PERIOD => successfully transmitted packets within a gap period
	 *   LOST_IN_BURST_PERIOD => isolated losses within a gap period
	 *   LOST_IN_GAP_PERIOD => lost packets within a burst period
	 *   TX_IN_GAP_PERIOD => successfully transmitted packets within a burst period
	 */
	switch (clg->state) {
	case TX_IN_GAP_PERIOD:
		if (rnd < clg->a4) {
			clg->state = LOST_IN_BURST_PERIOD;
			return true;
		} else if (clg->a4 < rnd && rnd < clg->a1 + clg->a4) {
			clg->state = LOST_IN_GAP_PERIOD;
			return true;
		} else if (clg->a1 + clg->a4 < rnd) {
			clg->state = TX_IN_GAP_PERIOD;
		}

		break;
	case TX_IN_BURST_PERIOD:
		if (rnd < clg->a5) {
			clg->state = LOST_IN_GAP_PERIOD;
			return true;
		} else {
			clg->state = TX_IN_BURST_PERIOD;
		}

		break;
	case LOST_IN_GAP_PERIOD:
		if (rnd < clg->a3)
			clg->state = TX_IN_BURST_PERIOD;
		else if (clg->a3 < rnd && rnd < clg->a2 + clg->a3) {
			clg->state = TX_IN_GAP_PERIOD;
		} else if (clg->a2 + clg->a3 < rnd) {
			clg->state = LOST_IN_GAP_PERIOD;
			return true;
		}
		break;
	case LOST_IN_BURST_PERIOD:
		clg->state = TX_IN_GAP_PERIOD;
		break;
	}

	return false;
}