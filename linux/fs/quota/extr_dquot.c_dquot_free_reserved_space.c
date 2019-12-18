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
typedef  scalar_t__ time64_t ;
struct TYPE_2__ {scalar_t__ dqb_rsvspace; scalar_t__ dqb_curspace; scalar_t__ dqb_bsoftlimit; scalar_t__ dqb_btime; } ;
struct dquot {int /*<<< orphan*/  dq_flags; TYPE_1__ dq_dqb; } ;
typedef  scalar_t__ qsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DQ_BLKS_B ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline
void dquot_free_reserved_space(struct dquot *dquot, qsize_t number)
{
	if (dquot->dq_dqb.dqb_rsvspace >= number)
		dquot->dq_dqb.dqb_rsvspace -= number;
	else {
		WARN_ON_ONCE(1);
		dquot->dq_dqb.dqb_rsvspace = 0;
	}
	if (dquot->dq_dqb.dqb_curspace + dquot->dq_dqb.dqb_rsvspace <=
	    dquot->dq_dqb.dqb_bsoftlimit)
		dquot->dq_dqb.dqb_btime = (time64_t) 0;
	clear_bit(DQ_BLKS_B, &dquot->dq_flags);
}