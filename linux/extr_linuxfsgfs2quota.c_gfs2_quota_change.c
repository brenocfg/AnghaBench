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
typedef  size_t u32 ;
struct TYPE_4__ {scalar_t__ ar_quota; } ;
struct gfs2_sbd {TYPE_2__ sd_args; } ;
struct gfs2_quota_data {int /*<<< orphan*/  qd_id; } ;
struct gfs2_inode {int i_diskflags; TYPE_1__* i_qadata; int /*<<< orphan*/  i_inode; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
struct TYPE_3__ {size_t qa_qd_num; struct gfs2_quota_data** qa_qd; } ;

/* Variables and functions */
 int GFS2_DIF_SYSTEM ; 
 scalar_t__ GFS2_QUOTA_ON ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_qc (struct gfs2_quota_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ gfs2_assert_warn (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kqid_gid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kqid_uid (int /*<<< orphan*/ ) ; 
 scalar_t__ qid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gfs2_quota_change(struct gfs2_inode *ip, s64 change,
		       kuid_t uid, kgid_t gid)
{
	struct gfs2_quota_data *qd;
	u32 x;
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);

	if (sdp->sd_args.ar_quota != GFS2_QUOTA_ON ||
	    gfs2_assert_warn(sdp, change))
		return;
	if (ip->i_diskflags & GFS2_DIF_SYSTEM)
		return;

	for (x = 0; x < ip->i_qadata->qa_qd_num; x++) {
		qd = ip->i_qadata->qa_qd[x];

		if (qid_eq(qd->qd_id, make_kqid_uid(uid)) ||
		    qid_eq(qd->qd_id, make_kqid_gid(gid))) {
			do_qc(qd, change);
		}
	}
}