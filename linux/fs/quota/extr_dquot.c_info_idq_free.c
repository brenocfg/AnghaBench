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
struct TYPE_4__ {scalar_t__ dqb_curinodes; scalar_t__ dqb_isoftlimit; scalar_t__ dqb_ihardlimit; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct dquot {TYPE_2__ dq_dqb; TYPE_1__ dq_id; int /*<<< orphan*/  dq_sb; int /*<<< orphan*/  dq_flags; } ;
typedef  scalar_t__ qsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DQ_FAKE_B ; 
 int QUOTA_NL_IHARDBELOW ; 
 int QUOTA_NL_ISOFTBELOW ; 
 int QUOTA_NL_NOWARN ; 
 int /*<<< orphan*/  sb_has_quota_limits_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int info_idq_free(struct dquot *dquot, qsize_t inodes)
{
	qsize_t newinodes;

	if (test_bit(DQ_FAKE_B, &dquot->dq_flags) ||
	    dquot->dq_dqb.dqb_curinodes <= dquot->dq_dqb.dqb_isoftlimit ||
	    !sb_has_quota_limits_enabled(dquot->dq_sb, dquot->dq_id.type))
		return QUOTA_NL_NOWARN;

	newinodes = dquot->dq_dqb.dqb_curinodes - inodes;
	if (newinodes <= dquot->dq_dqb.dqb_isoftlimit)
		return QUOTA_NL_ISOFTBELOW;
	if (dquot->dq_dqb.dqb_curinodes >= dquot->dq_dqb.dqb_ihardlimit &&
	    newinodes < dquot->dq_dqb.dqb_ihardlimit)
		return QUOTA_NL_IHARDBELOW;
	return QUOTA_NL_NOWARN;
}