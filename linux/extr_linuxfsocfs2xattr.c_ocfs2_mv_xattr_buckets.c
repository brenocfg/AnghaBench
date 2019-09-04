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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_xattr_bucket {int dummy; } ;
struct ocfs2_super {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {TYPE_1__* xh_entries; int /*<<< orphan*/  xh_num_buckets; } ;
struct TYPE_3__ {int /*<<< orphan*/  xe_name_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 TYPE_2__* bucket_xh (struct ocfs2_xattr_bucket*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_blocks_per_xattr_bucket (int /*<<< orphan*/ ) ; 
 int ocfs2_cp_xattr_bucket (struct inode*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 int ocfs2_extend_trans (int /*<<< orphan*/ *,int) ; 
 int ocfs2_read_xattr_bucket (struct ocfs2_xattr_bucket*,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_free (struct ocfs2_xattr_bucket*) ; 
 int ocfs2_xattr_bucket_journal_access (int /*<<< orphan*/ *,struct ocfs2_xattr_bucket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_journal_dirty (int /*<<< orphan*/ *,struct ocfs2_xattr_bucket*) ; 
 struct ocfs2_xattr_bucket* ocfs2_xattr_bucket_new (struct inode*) ; 
 int ocfs2_xattr_buckets_per_cluster (struct ocfs2_super*) ; 
 int /*<<< orphan*/  trace_ocfs2_mv_xattr_buckets (unsigned long long,unsigned long long) ; 

__attribute__((used)) static int ocfs2_mv_xattr_buckets(struct inode *inode, handle_t *handle,
				  u64 src_blk, u64 last_blk, u64 to_blk,
				  unsigned int start_bucket,
				  u32 *first_hash)
{
	int i, ret, credits;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	int blks_per_bucket = ocfs2_blocks_per_xattr_bucket(inode->i_sb);
	int num_buckets = ocfs2_xattr_buckets_per_cluster(osb);
	struct ocfs2_xattr_bucket *old_first, *new_first;

	trace_ocfs2_mv_xattr_buckets((unsigned long long)last_blk,
				     (unsigned long long)to_blk);

	BUG_ON(start_bucket >= num_buckets);
	if (start_bucket) {
		num_buckets -= start_bucket;
		last_blk += (start_bucket * blks_per_bucket);
	}

	/* The first bucket of the original extent */
	old_first = ocfs2_xattr_bucket_new(inode);
	/* The first bucket of the new extent */
	new_first = ocfs2_xattr_bucket_new(inode);
	if (!old_first || !new_first) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_read_xattr_bucket(old_first, src_blk);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	/*
	 * We need to update the first bucket of the old extent and all
	 * the buckets going to the new extent.
	 */
	credits = ((num_buckets + 1) * blks_per_bucket);
	ret = ocfs2_extend_trans(handle, credits);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_xattr_bucket_journal_access(handle, old_first,
						OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	for (i = 0; i < num_buckets; i++) {
		ret = ocfs2_cp_xattr_bucket(inode, handle,
					    last_blk + (i * blks_per_bucket),
					    to_blk + (i * blks_per_bucket),
					    1);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
	}

	/*
	 * Get the new bucket ready before we dirty anything
	 * (This actually shouldn't fail, because we already dirtied
	 * it once in ocfs2_cp_xattr_bucket()).
	 */
	ret = ocfs2_read_xattr_bucket(new_first, to_blk);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}
	ret = ocfs2_xattr_bucket_journal_access(handle, new_first,
						OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	/* Now update the headers */
	le16_add_cpu(&bucket_xh(old_first)->xh_num_buckets, -num_buckets);
	ocfs2_xattr_bucket_journal_dirty(handle, old_first);

	bucket_xh(new_first)->xh_num_buckets = cpu_to_le16(num_buckets);
	ocfs2_xattr_bucket_journal_dirty(handle, new_first);

	if (first_hash)
		*first_hash = le32_to_cpu(bucket_xh(new_first)->xh_entries[0].xe_name_hash);

out:
	ocfs2_xattr_bucket_free(new_first);
	ocfs2_xattr_bucket_free(old_first);
	return ret;
}