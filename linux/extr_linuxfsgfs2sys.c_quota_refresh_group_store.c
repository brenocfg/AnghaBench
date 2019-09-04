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
typedef  int /*<<< orphan*/  u32 ;
struct kqid {int dummy; } ;
struct gfs2_sbd {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  GRPQUOTA ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int gfs2_quota_refresh (struct gfs2_sbd*,struct kqid) ; 
 int kstrtou32 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct kqid make_kqid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qid_valid (struct kqid) ; 

__attribute__((used)) static ssize_t quota_refresh_group_store(struct gfs2_sbd *sdp, const char *buf,
					 size_t len)
{
	struct kqid qid;
	int error;
	u32 id;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	error = kstrtou32(buf, 0, &id);
	if (error)
		return error;

	qid = make_kqid(current_user_ns(), GRPQUOTA, id);
	if (!qid_valid(qid))
		return -EINVAL;

	error = gfs2_quota_refresh(sdp, qid);
	return error ? error : len;
}