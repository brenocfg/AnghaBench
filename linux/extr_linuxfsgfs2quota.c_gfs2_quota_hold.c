#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ar_quota; } ;
struct gfs2_sbd {TYPE_1__ sd_args; } ;
struct gfs2_quota_data {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct gfs2_inode {TYPE_2__* i_qadata; TYPE_3__ i_inode; int /*<<< orphan*/  i_flags; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
struct TYPE_5__ {int /*<<< orphan*/  qa_qd_num; struct gfs2_quota_data** qa_qd; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ GFS2_QUOTA_OFF ; 
 struct gfs2_sbd* GFS2_SB (TYPE_3__*) ; 
 int /*<<< orphan*/  GIF_QD_LOCKED ; 
 int /*<<< orphan*/  NO_GID_QUOTA_CHANGE ; 
 int /*<<< orphan*/  NO_UID_QUOTA_CHANGE ; 
 scalar_t__ gfs2_assert_warn (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  gfs2_quota_unhold (struct gfs2_inode*) ; 
 int gfs2_rsqa_alloc (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kqid_gid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kqid_uid (int /*<<< orphan*/ ) ; 
 int qdsb_get (struct gfs2_sbd*,int /*<<< orphan*/ ,struct gfs2_quota_data**) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int gfs2_quota_hold(struct gfs2_inode *ip, kuid_t uid, kgid_t gid)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct gfs2_quota_data **qd;
	int error;

	if (sdp->sd_args.ar_quota == GFS2_QUOTA_OFF)
		return 0;

	if (ip->i_qadata == NULL) {
		error = gfs2_rsqa_alloc(ip);
		if (error)
			return error;
	}

	qd = ip->i_qadata->qa_qd;

	if (gfs2_assert_warn(sdp, !ip->i_qadata->qa_qd_num) ||
	    gfs2_assert_warn(sdp, !test_bit(GIF_QD_LOCKED, &ip->i_flags)))
		return -EIO;

	error = qdsb_get(sdp, make_kqid_uid(ip->i_inode.i_uid), qd);
	if (error)
		goto out;
	ip->i_qadata->qa_qd_num++;
	qd++;

	error = qdsb_get(sdp, make_kqid_gid(ip->i_inode.i_gid), qd);
	if (error)
		goto out;
	ip->i_qadata->qa_qd_num++;
	qd++;

	if (!uid_eq(uid, NO_UID_QUOTA_CHANGE) &&
	    !uid_eq(uid, ip->i_inode.i_uid)) {
		error = qdsb_get(sdp, make_kqid_uid(uid), qd);
		if (error)
			goto out;
		ip->i_qadata->qa_qd_num++;
		qd++;
	}

	if (!gid_eq(gid, NO_GID_QUOTA_CHANGE) &&
	    !gid_eq(gid, ip->i_inode.i_gid)) {
		error = qdsb_get(sdp, make_kqid_gid(gid), qd);
		if (error)
			goto out;
		ip->i_qadata->qa_qd_num++;
		qd++;
	}

out:
	if (error)
		gfs2_quota_unhold(ip);
	return error;
}