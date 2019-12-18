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
struct TYPE_3__ {scalar_t__ ar_quota; } ;
struct gfs2_sbd {TYPE_1__ sd_args; } ;
struct gfs2_quota_data {int dummy; } ;
struct gfs2_inode {TYPE_2__* i_qadata; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_inode; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
struct TYPE_4__ {size_t qa_qd_num; int /*<<< orphan*/ * qa_qd_ghs; struct gfs2_quota_data** qa_qd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 scalar_t__ GFS2_QUOTA_ON ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIF_QD_LOCKED ; 
 int /*<<< orphan*/  NO_FORCE ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int do_glock (struct gfs2_quota_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (int /*<<< orphan*/ *) ; 
 int gfs2_quota_hold (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_quota_unhold (struct gfs2_inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sort (struct gfs2_quota_data**,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sort_qd ; 

int gfs2_quota_lock(struct gfs2_inode *ip, kuid_t uid, kgid_t gid)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct gfs2_quota_data *qd;
	u32 x;
	int error = 0;

	if (capable(CAP_SYS_RESOURCE) ||
	    sdp->sd_args.ar_quota != GFS2_QUOTA_ON)
		return 0;

	error = gfs2_quota_hold(ip, uid, gid);
	if (error)
		return error;

	sort(ip->i_qadata->qa_qd, ip->i_qadata->qa_qd_num,
	     sizeof(struct gfs2_quota_data *), sort_qd, NULL);

	for (x = 0; x < ip->i_qadata->qa_qd_num; x++) {
		qd = ip->i_qadata->qa_qd[x];
		error = do_glock(qd, NO_FORCE, &ip->i_qadata->qa_qd_ghs[x]);
		if (error)
			break;
	}

	if (!error)
		set_bit(GIF_QD_LOCKED, &ip->i_flags);
	else {
		while (x--)
			gfs2_glock_dq_uninit(&ip->i_qadata->qa_qd_ghs[x]);
		gfs2_quota_unhold(ip);
	}

	return error;
}