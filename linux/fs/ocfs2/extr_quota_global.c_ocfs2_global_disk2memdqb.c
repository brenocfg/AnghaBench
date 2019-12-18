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
struct ocfs2_global_disk_dqblk {int /*<<< orphan*/  dqb_use_count; int /*<<< orphan*/  dqb_itime; int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_curspace; int /*<<< orphan*/  dqb_bsoftlimit; int /*<<< orphan*/  dqb_bhardlimit; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; } ;
struct mem_dqblk {void* dqb_itime; void* dqb_btime; void* dqb_curspace; void* dqb_bsoftlimit; void* dqb_bhardlimit; void* dqb_curinodes; void* dqb_isoftlimit; void* dqb_ihardlimit; } ;
struct dquot {int /*<<< orphan*/  dq_flags; struct mem_dqblk dq_dqb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dq_use_count; } ;

/* Variables and functions */
 scalar_t__ DQ_LASTSET_B ; 
 TYPE_1__* OCFS2_DQUOT (struct dquot*) ; 
 scalar_t__ QIF_BLIMITS_B ; 
 scalar_t__ QIF_BTIME_B ; 
 scalar_t__ QIF_ILIMITS_B ; 
 scalar_t__ QIF_INODES_B ; 
 scalar_t__ QIF_ITIME_B ; 
 scalar_t__ QIF_SPACE_B ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_global_disk2memdqb(struct dquot *dquot, void *dp)
{
	struct ocfs2_global_disk_dqblk *d = dp;
	struct mem_dqblk *m = &dquot->dq_dqb;

	/* Update from disk only entries not set by the admin */
	if (!test_bit(DQ_LASTSET_B + QIF_ILIMITS_B, &dquot->dq_flags)) {
		m->dqb_ihardlimit = le64_to_cpu(d->dqb_ihardlimit);
		m->dqb_isoftlimit = le64_to_cpu(d->dqb_isoftlimit);
	}
	if (!test_bit(DQ_LASTSET_B + QIF_INODES_B, &dquot->dq_flags))
		m->dqb_curinodes = le64_to_cpu(d->dqb_curinodes);
	if (!test_bit(DQ_LASTSET_B + QIF_BLIMITS_B, &dquot->dq_flags)) {
		m->dqb_bhardlimit = le64_to_cpu(d->dqb_bhardlimit);
		m->dqb_bsoftlimit = le64_to_cpu(d->dqb_bsoftlimit);
	}
	if (!test_bit(DQ_LASTSET_B + QIF_SPACE_B, &dquot->dq_flags))
		m->dqb_curspace = le64_to_cpu(d->dqb_curspace);
	if (!test_bit(DQ_LASTSET_B + QIF_BTIME_B, &dquot->dq_flags))
		m->dqb_btime = le64_to_cpu(d->dqb_btime);
	if (!test_bit(DQ_LASTSET_B + QIF_ITIME_B, &dquot->dq_flags))
		m->dqb_itime = le64_to_cpu(d->dqb_itime);
	OCFS2_DQUOT(dquot)->dq_use_count = le32_to_cpu(d->dqb_use_count);
}