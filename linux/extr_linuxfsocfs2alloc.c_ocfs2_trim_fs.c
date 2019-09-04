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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct super_block {scalar_t__ s_blocksize; } ;
struct ocfs2_trim_fs_info {int tf_success; scalar_t__ tf_start; scalar_t__ tf_len; scalar_t__ tf_minlen; scalar_t__ tf_trimlen; int /*<<< orphan*/  tf_nodenum; scalar_t__ tf_valid; } ;
struct ocfs2_super {scalar_t__ s_clustersize_bits; scalar_t__ bitmap_cpg; scalar_t__ first_cluster_group_blkno; int /*<<< orphan*/  node_num; int /*<<< orphan*/  dev_str; } ;
struct ocfs2_group_desc {int dummy; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_clusters; } ;
struct inode {int dummy; } ;
struct fstrim_range {scalar_t__ start; scalar_t__ len; scalar_t__ minlen; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  GLOBAL_BITMAP_SYSTEM_INODE ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 int /*<<< orphan*/  OCFS2_INVALID_SLOT ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_blocks_to_clusters (struct super_block*,scalar_t__) ; 
 scalar_t__ ocfs2_clusters_to_blocks (struct super_block*,scalar_t__) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 int ocfs2_read_group_descriptor (struct inode*,struct ocfs2_dinode*,scalar_t__,struct buffer_head**) ; 
 int ocfs2_trim_fs_lock (struct ocfs2_super*,struct ocfs2_trim_fs_info*,int) ; 
 int /*<<< orphan*/  ocfs2_trim_fs_lock_res_init (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_trim_fs_lock_res_uninit (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_trim_fs_unlock (struct ocfs2_super*,struct ocfs2_trim_fs_info*) ; 
 int ocfs2_trim_group (struct super_block*,struct ocfs2_group_desc*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ ocfs2_which_cluster_group (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  trace_ocfs2_trim_fs (scalar_t__,scalar_t__,scalar_t__) ; 

int ocfs2_trim_fs(struct super_block *sb, struct fstrim_range *range)
{
	struct ocfs2_super *osb = OCFS2_SB(sb);
	u64 start, len, trimmed, first_group, last_group, group;
	int ret, cnt;
	u32 first_bit, last_bit, minlen;
	struct buffer_head *main_bm_bh = NULL;
	struct inode *main_bm_inode = NULL;
	struct buffer_head *gd_bh = NULL;
	struct ocfs2_dinode *main_bm;
	struct ocfs2_group_desc *gd = NULL;
	struct ocfs2_trim_fs_info info, *pinfo = NULL;

	start = range->start >> osb->s_clustersize_bits;
	len = range->len >> osb->s_clustersize_bits;
	minlen = range->minlen >> osb->s_clustersize_bits;

	if (minlen >= osb->bitmap_cpg || range->len < sb->s_blocksize)
		return -EINVAL;

	main_bm_inode = ocfs2_get_system_file_inode(osb,
						    GLOBAL_BITMAP_SYSTEM_INODE,
						    OCFS2_INVALID_SLOT);
	if (!main_bm_inode) {
		ret = -EIO;
		mlog_errno(ret);
		goto out;
	}

	inode_lock(main_bm_inode);

	ret = ocfs2_inode_lock(main_bm_inode, &main_bm_bh, 0);
	if (ret < 0) {
		mlog_errno(ret);
		goto out_mutex;
	}
	main_bm = (struct ocfs2_dinode *)main_bm_bh->b_data;

	if (start >= le32_to_cpu(main_bm->i_clusters)) {
		ret = -EINVAL;
		goto out_unlock;
	}

	len = range->len >> osb->s_clustersize_bits;
	if (start + len > le32_to_cpu(main_bm->i_clusters))
		len = le32_to_cpu(main_bm->i_clusters) - start;

	trace_ocfs2_trim_fs(start, len, minlen);

	ocfs2_trim_fs_lock_res_init(osb);
	ret = ocfs2_trim_fs_lock(osb, NULL, 1);
	if (ret < 0) {
		if (ret != -EAGAIN) {
			mlog_errno(ret);
			ocfs2_trim_fs_lock_res_uninit(osb);
			goto out_unlock;
		}

		mlog(ML_NOTICE, "Wait for trim on device (%s) to "
		     "finish, which is running from another node.\n",
		     osb->dev_str);
		ret = ocfs2_trim_fs_lock(osb, &info, 0);
		if (ret < 0) {
			mlog_errno(ret);
			ocfs2_trim_fs_lock_res_uninit(osb);
			goto out_unlock;
		}

		if (info.tf_valid && info.tf_success &&
		    info.tf_start == start && info.tf_len == len &&
		    info.tf_minlen == minlen) {
			/* Avoid sending duplicated trim to a shared device */
			mlog(ML_NOTICE, "The same trim on device (%s) was "
			     "just done from node (%u), return.\n",
			     osb->dev_str, info.tf_nodenum);
			range->len = info.tf_trimlen;
			goto out_trimunlock;
		}
	}

	info.tf_nodenum = osb->node_num;
	info.tf_start = start;
	info.tf_len = len;
	info.tf_minlen = minlen;

	/* Determine first and last group to examine based on start and len */
	first_group = ocfs2_which_cluster_group(main_bm_inode, start);
	if (first_group == osb->first_cluster_group_blkno)
		first_bit = start;
	else
		first_bit = start - ocfs2_blocks_to_clusters(sb, first_group);
	last_group = ocfs2_which_cluster_group(main_bm_inode, start + len - 1);
	last_bit = osb->bitmap_cpg;

	trimmed = 0;
	for (group = first_group; group <= last_group;) {
		if (first_bit + len >= osb->bitmap_cpg)
			last_bit = osb->bitmap_cpg;
		else
			last_bit = first_bit + len;

		ret = ocfs2_read_group_descriptor(main_bm_inode,
						  main_bm, group,
						  &gd_bh);
		if (ret < 0) {
			mlog_errno(ret);
			break;
		}

		gd = (struct ocfs2_group_desc *)gd_bh->b_data;
		cnt = ocfs2_trim_group(sb, gd, group,
				       first_bit, last_bit, minlen);
		brelse(gd_bh);
		gd_bh = NULL;
		if (cnt < 0) {
			ret = cnt;
			mlog_errno(ret);
			break;
		}

		trimmed += cnt;
		len -= osb->bitmap_cpg - first_bit;
		first_bit = 0;
		if (group == osb->first_cluster_group_blkno)
			group = ocfs2_clusters_to_blocks(sb, osb->bitmap_cpg);
		else
			group += ocfs2_clusters_to_blocks(sb, osb->bitmap_cpg);
	}
	range->len = trimmed * sb->s_blocksize;

	info.tf_trimlen = range->len;
	info.tf_success = (ret ? 0 : 1);
	pinfo = &info;
out_trimunlock:
	ocfs2_trim_fs_unlock(osb, pinfo);
	ocfs2_trim_fs_lock_res_uninit(osb);
out_unlock:
	ocfs2_inode_unlock(main_bm_inode, 0);
	brelse(main_bm_bh);
out_mutex:
	inode_unlock(main_bm_inode);
	iput(main_bm_inode);
out:
	return ret;
}