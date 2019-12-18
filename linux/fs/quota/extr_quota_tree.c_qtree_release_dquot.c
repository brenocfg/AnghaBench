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
struct qtree_mem_dqinfo {int dummy; } ;
struct TYPE_2__ {int dqb_curinodes; int dqb_curspace; } ;
struct dquot {TYPE_1__ dq_dqb; int /*<<< orphan*/  dq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQ_FAKE_B ; 
 int qtree_delete_dquot (struct qtree_mem_dqinfo*,struct dquot*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qtree_release_dquot(struct qtree_mem_dqinfo *info, struct dquot *dquot)
{
	if (test_bit(DQ_FAKE_B, &dquot->dq_flags) &&
	    !(dquot->dq_dqb.dqb_curinodes | dquot->dq_dqb.dqb_curspace))
		return qtree_delete_dquot(info, dquot);
	return 0;
}