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
struct super_block {int dummy; } ;
struct ocfs2_trim_fs_info {int tf_success; scalar_t__ tf_start; scalar_t__ tf_len; scalar_t__ tf_minlen; scalar_t__ tf_trimlen; int /*<<< orphan*/  tf_nodenum; scalar_t__ tf_valid; } ;
struct ocfs2_super {int /*<<< orphan*/  node_num; int /*<<< orphan*/  dev_str; } ;
struct fstrim_range {scalar_t__ start; scalar_t__ len; scalar_t__ minlen; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_trim_fs_lock (struct ocfs2_super*,struct ocfs2_trim_fs_info*,int) ; 
 int /*<<< orphan*/  ocfs2_trim_fs_lock_res_init (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_trim_fs_lock_res_uninit (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_trim_fs_unlock (struct ocfs2_super*,struct ocfs2_trim_fs_info*) ; 
 int ocfs2_trim_mainbm (struct super_block*,struct fstrim_range*) ; 
 int /*<<< orphan*/  trace_ocfs2_trim_fs (scalar_t__,scalar_t__,scalar_t__) ; 

int ocfs2_trim_fs(struct super_block *sb, struct fstrim_range *range)
{
	int ret;
	struct ocfs2_super *osb = OCFS2_SB(sb);
	struct ocfs2_trim_fs_info info, *pinfo = NULL;

	ocfs2_trim_fs_lock_res_init(osb);

	trace_ocfs2_trim_fs(range->start, range->len, range->minlen);

	ret = ocfs2_trim_fs_lock(osb, NULL, 1);
	if (ret < 0) {
		if (ret != -EAGAIN) {
			mlog_errno(ret);
			ocfs2_trim_fs_lock_res_uninit(osb);
			return ret;
		}

		mlog(ML_NOTICE, "Wait for trim on device (%s) to "
		     "finish, which is running from another node.\n",
		     osb->dev_str);
		ret = ocfs2_trim_fs_lock(osb, &info, 0);
		if (ret < 0) {
			mlog_errno(ret);
			ocfs2_trim_fs_lock_res_uninit(osb);
			return ret;
		}

		if (info.tf_valid && info.tf_success &&
		    info.tf_start == range->start &&
		    info.tf_len == range->len &&
		    info.tf_minlen == range->minlen) {
			/* Avoid sending duplicated trim to a shared device */
			mlog(ML_NOTICE, "The same trim on device (%s) was "
			     "just done from node (%u), return.\n",
			     osb->dev_str, info.tf_nodenum);
			range->len = info.tf_trimlen;
			goto out;
		}
	}

	info.tf_nodenum = osb->node_num;
	info.tf_start = range->start;
	info.tf_len = range->len;
	info.tf_minlen = range->minlen;

	ret = ocfs2_trim_mainbm(sb, range);

	info.tf_trimlen = range->len;
	info.tf_success = (ret < 0 ? 0 : 1);
	pinfo = &info;
out:
	ocfs2_trim_fs_unlock(osb, pinfo);
	ocfs2_trim_fs_lock_res_uninit(osb);
	return ret;
}