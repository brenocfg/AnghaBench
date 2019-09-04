#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time64_t ;
struct TYPE_3__ {scalar_t__ dqb_curspace; scalar_t__ dqb_rsvspace; scalar_t__ dqb_bsoftlimit; scalar_t__ dqb_btime; } ;
struct dquot {int /*<<< orphan*/  dq_flags; TYPE_1__ dq_dqb; int /*<<< orphan*/  dq_sb; } ;
typedef  scalar_t__ qsize_t ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int DQUOT_NEGATIVE_USAGE ; 
 int /*<<< orphan*/  DQ_BLKS_B ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* sb_dqopt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dquot_decr_space(struct dquot *dquot, qsize_t number)
{
	if (sb_dqopt(dquot->dq_sb)->flags & DQUOT_NEGATIVE_USAGE ||
	    dquot->dq_dqb.dqb_curspace >= number)
		dquot->dq_dqb.dqb_curspace -= number;
	else
		dquot->dq_dqb.dqb_curspace = 0;
	if (dquot->dq_dqb.dqb_curspace + dquot->dq_dqb.dqb_rsvspace <=
	    dquot->dq_dqb.dqb_bsoftlimit)
		dquot->dq_dqb.dqb_btime = (time64_t) 0;
	clear_bit(DQ_BLKS_B, &dquot->dq_flags);
}