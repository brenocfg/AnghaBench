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
struct clgstate {int state; int /*<<< orphan*/  a3; int /*<<< orphan*/  a2; int /*<<< orphan*/  a4; int /*<<< orphan*/  a1; } ;
struct netem_sched_data {struct clgstate clg; } ;

/* Variables and functions */
#define  BAD_STATE 129 
#define  GOOD_STATE 128 
 int /*<<< orphan*/  prandom_u32 () ; 

__attribute__((used)) static bool loss_gilb_ell(struct netem_sched_data *q)
{
	struct clgstate *clg = &q->clg;

	switch (clg->state) {
	case GOOD_STATE:
		if (prandom_u32() < clg->a1)
			clg->state = BAD_STATE;
		if (prandom_u32() < clg->a4)
			return true;
		break;
	case BAD_STATE:
		if (prandom_u32() < clg->a2)
			clg->state = GOOD_STATE;
		if (prandom_u32() > clg->a3)
			return true;
	}

	return false;
}