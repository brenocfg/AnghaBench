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
struct ocfs2_super {int dummy; } ;
struct ocfs2_dir_lookup_result {struct buffer_head* dl_leaf_bh; int /*<<< orphan*/  dl_hinfo; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int ip_dyn_features; scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENOSPC ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_dir_indexed (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_dx_dir_name_hash (struct inode*,char const*,int,int /*<<< orphan*/ *) ; 
 int ocfs2_extend_dir (struct ocfs2_super*,struct inode*,struct buffer_head*,unsigned int,struct ocfs2_dir_lookup_result*,struct buffer_head**) ; 
 int ocfs2_find_dir_space_el (struct inode*,char const*,int,struct buffer_head**) ; 
 int ocfs2_find_dir_space_id (struct inode*,struct buffer_head*,char const*,int,struct buffer_head**,unsigned int*) ; 
 int ocfs2_prepare_dx_dir_for_insert (struct inode*,struct buffer_head*,char const*,int,struct ocfs2_dir_lookup_result*) ; 
 scalar_t__ ocfs2_supports_indexed_dirs (struct ocfs2_super*) ; 
 int /*<<< orphan*/  trace_ocfs2_prepare_dir_for_insert (unsigned long long,int) ; 

int ocfs2_prepare_dir_for_insert(struct ocfs2_super *osb,
				 struct inode *dir,
				 struct buffer_head *parent_fe_bh,
				 const char *name,
				 int namelen,
				 struct ocfs2_dir_lookup_result *lookup)
{
	int ret;
	unsigned int blocks_wanted = 1;
	struct buffer_head *bh = NULL;

	trace_ocfs2_prepare_dir_for_insert(
		(unsigned long long)OCFS2_I(dir)->ip_blkno, namelen);

	if (!namelen) {
		ret = -EINVAL;
		mlog_errno(ret);
		goto out;
	}

	/*
	 * Do this up front to reduce confusion.
	 *
	 * The directory might start inline, then be turned into an
	 * indexed one, in which case we'd need to hash deep inside
	 * ocfs2_find_dir_space_id(). Since
	 * ocfs2_prepare_dx_dir_for_insert() also needs this hash
	 * done, there seems no point in spreading out the calls. We
	 * can optimize away the case where the file system doesn't
	 * support indexing.
	 */
	if (ocfs2_supports_indexed_dirs(osb))
		ocfs2_dx_dir_name_hash(dir, name, namelen, &lookup->dl_hinfo);

	if (ocfs2_dir_indexed(dir)) {
		ret = ocfs2_prepare_dx_dir_for_insert(dir, parent_fe_bh,
						      name, namelen, lookup);
		if (ret)
			mlog_errno(ret);
		goto out;
	}

	if (OCFS2_I(dir)->ip_dyn_features & OCFS2_INLINE_DATA_FL) {
		ret = ocfs2_find_dir_space_id(dir, parent_fe_bh, name,
					      namelen, &bh, &blocks_wanted);
	} else
		ret = ocfs2_find_dir_space_el(dir, name, namelen, &bh);

	if (ret && ret != -ENOSPC) {
		mlog_errno(ret);
		goto out;
	}

	if (ret == -ENOSPC) {
		/*
		 * We have to expand the directory to add this name.
		 */
		BUG_ON(bh);

		ret = ocfs2_extend_dir(osb, dir, parent_fe_bh, blocks_wanted,
				       lookup, &bh);
		if (ret) {
			if (ret != -ENOSPC)
				mlog_errno(ret);
			goto out;
		}

		BUG_ON(!bh);
	}

	lookup->dl_leaf_bh = bh;
	bh = NULL;
out:
	brelse(bh);
	return ret;
}