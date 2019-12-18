#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct v1_disk_dqblk {int dummy; } ;
struct quota_info {int /*<<< orphan*/ * files; } ;
struct TYPE_7__ {scalar_t__ dqb_bhardlimit; scalar_t__ dqb_bsoftlimit; scalar_t__ dqb_ihardlimit; scalar_t__ dqb_isoftlimit; } ;
struct TYPE_9__ {int type; } ;
struct dquot {int /*<<< orphan*/  dq_flags; TYPE_2__ dq_dqb; TYPE_5__ dq_id; TYPE_3__* dq_sb; } ;
struct TYPE_8__ {TYPE_1__* s_op; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* quota_read ) (TYPE_3__*,int,char*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DQST_READS ; 
 int /*<<< orphan*/  DQ_FAKE_B ; 
 int EINVAL ; 
 int /*<<< orphan*/  dqstats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kqid (int /*<<< orphan*/ *,TYPE_5__) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  memset (struct v1_disk_dqblk*,int /*<<< orphan*/ ,int) ; 
 struct quota_info* sb_dqopt (TYPE_3__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v1_disk2mem_dqblk (TYPE_2__*,struct v1_disk_dqblk*) ; 
 int /*<<< orphan*/  v1_dqoff (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int v1_read_dqblk(struct dquot *dquot)
{
	int type = dquot->dq_id.type;
	struct v1_disk_dqblk dqblk;
	struct quota_info *dqopt = sb_dqopt(dquot->dq_sb);

	if (!dqopt->files[type])
		return -EINVAL;

	/* Set structure to 0s in case read fails/is after end of file */
	memset(&dqblk, 0, sizeof(struct v1_disk_dqblk));
	dquot->dq_sb->s_op->quota_read(dquot->dq_sb, type, (char *)&dqblk,
			sizeof(struct v1_disk_dqblk),
			v1_dqoff(from_kqid(&init_user_ns, dquot->dq_id)));

	v1_disk2mem_dqblk(&dquot->dq_dqb, &dqblk);
	if (dquot->dq_dqb.dqb_bhardlimit == 0 &&
	    dquot->dq_dqb.dqb_bsoftlimit == 0 &&
	    dquot->dq_dqb.dqb_ihardlimit == 0 &&
	    dquot->dq_dqb.dqb_isoftlimit == 0)
		set_bit(DQ_FAKE_B, &dquot->dq_flags);
	dqstats_inc(DQST_READS);

	return 0;
}