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
struct ocfs2_xattr_set_ctxt {int /*<<< orphan*/  dealloc; scalar_t__ meta_ac; scalar_t__ data_ac; int /*<<< orphan*/  handle; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct ocfs2_xattr_search {int not_found; int /*<<< orphan*/  bucket; struct buffer_head* xattr_bh; struct buffer_head* inode_bh; } ;
struct ocfs2_xattr_info {int xi_name_index; char const* xi_name; void const* xi_value; size_t xi_value_len; int /*<<< orphan*/  xi_name_len; } ;
struct ocfs2_super {struct inode* osb_tl_inode; } ;
struct ocfs2_refcount_tree {int dummy; } ;
struct ocfs2_lock_holder {int dummy; } ;
struct ocfs2_dinode {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_xattr_sem; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENODATA ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 scalar_t__ OCFS2_INODE_UPDATE_CREDITS ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int XATTR_CREATE ; 
 int XATTR_REPLACE ; 
 int __ocfs2_flush_truncate_log (struct ocfs2_super*) ; 
 int __ocfs2_xattr_set_handle (struct inode*,struct ocfs2_dinode*,struct ocfs2_xattr_info*,struct ocfs2_xattr_search*,struct ocfs2_xattr_search*,struct ocfs2_xattr_set_ctxt*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_dealloc_has_cluster (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (scalar_t__) ; 
 int ocfs2_init_xattr_set_ctxt (struct inode*,struct ocfs2_dinode*,struct ocfs2_xattr_info*,struct ocfs2_xattr_search*,struct ocfs2_xattr_search*,struct ocfs2_xattr_set_ctxt*,int,int*) ; 
 int ocfs2_inode_lock_tracker (struct inode*,struct buffer_head**,int,struct ocfs2_lock_holder*) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock_tracker (struct inode*,int,struct ocfs2_lock_holder*,int) ; 
 scalar_t__ ocfs2_is_refcount_inode (struct inode*) ; 
 int ocfs2_prepare_refcount_xattr (struct inode*,struct ocfs2_dinode*,struct ocfs2_xattr_info*,struct ocfs2_xattr_search*,struct ocfs2_xattr_search*,struct ocfs2_refcount_tree**,int*,int*) ; 
 int /*<<< orphan*/  ocfs2_run_deallocs (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_schedule_truncate_log_flush (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_start_trans (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_supports_xattr (struct ocfs2_super*) ; 
 scalar_t__ ocfs2_truncate_log_needs_flush (struct ocfs2_super*) ; 
 int ocfs2_try_remove_refcount_tree (struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_unlock_refcount_tree (struct ocfs2_super*,struct ocfs2_refcount_tree*,int) ; 
 int /*<<< orphan*/  ocfs2_update_inode_fsync_trans (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 
 int ocfs2_xattr_block_find (struct inode*,int,char const*,struct ocfs2_xattr_search*) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_new (struct inode*) ; 
 int ocfs2_xattr_ibody_find (struct inode*,int,char const*,struct ocfs2_xattr_search*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ocfs2_xattr_set(struct inode *inode,
		    int name_index,
		    const char *name,
		    const void *value,
		    size_t value_len,
		    int flags)
{
	struct buffer_head *di_bh = NULL;
	struct ocfs2_dinode *di;
	int ret, credits, had_lock, ref_meta = 0, ref_credits = 0;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct inode *tl_inode = osb->osb_tl_inode;
	struct ocfs2_xattr_set_ctxt ctxt = { NULL, NULL, NULL, };
	struct ocfs2_refcount_tree *ref_tree = NULL;
	struct ocfs2_lock_holder oh;

	struct ocfs2_xattr_info xi = {
		.xi_name_index = name_index,
		.xi_name = name,
		.xi_name_len = strlen(name),
		.xi_value = value,
		.xi_value_len = value_len,
	};

	struct ocfs2_xattr_search xis = {
		.not_found = -ENODATA,
	};

	struct ocfs2_xattr_search xbs = {
		.not_found = -ENODATA,
	};

	if (!ocfs2_supports_xattr(osb))
		return -EOPNOTSUPP;

	/*
	 * Only xbs will be used on indexed trees.  xis doesn't need a
	 * bucket.
	 */
	xbs.bucket = ocfs2_xattr_bucket_new(inode);
	if (!xbs.bucket) {
		mlog_errno(-ENOMEM);
		return -ENOMEM;
	}

	had_lock = ocfs2_inode_lock_tracker(inode, &di_bh, 1, &oh);
	if (had_lock < 0) {
		ret = had_lock;
		mlog_errno(ret);
		goto cleanup_nolock;
	}
	xis.inode_bh = xbs.inode_bh = di_bh;
	di = (struct ocfs2_dinode *)di_bh->b_data;

	down_write(&OCFS2_I(inode)->ip_xattr_sem);
	/*
	 * Scan inode and external block to find the same name
	 * extended attribute and collect search information.
	 */
	ret = ocfs2_xattr_ibody_find(inode, name_index, name, &xis);
	if (ret)
		goto cleanup;
	if (xis.not_found) {
		ret = ocfs2_xattr_block_find(inode, name_index, name, &xbs);
		if (ret)
			goto cleanup;
	}

	if (xis.not_found && xbs.not_found) {
		ret = -ENODATA;
		if (flags & XATTR_REPLACE)
			goto cleanup;
		ret = 0;
		if (!value)
			goto cleanup;
	} else {
		ret = -EEXIST;
		if (flags & XATTR_CREATE)
			goto cleanup;
	}

	/* Check whether the value is refcounted and do some preparation. */
	if (ocfs2_is_refcount_inode(inode) &&
	    (!xis.not_found || !xbs.not_found)) {
		ret = ocfs2_prepare_refcount_xattr(inode, di, &xi,
						   &xis, &xbs, &ref_tree,
						   &ref_meta, &ref_credits);
		if (ret) {
			mlog_errno(ret);
			goto cleanup;
		}
	}

	inode_lock(tl_inode);

	if (ocfs2_truncate_log_needs_flush(osb)) {
		ret = __ocfs2_flush_truncate_log(osb);
		if (ret < 0) {
			inode_unlock(tl_inode);
			mlog_errno(ret);
			goto cleanup;
		}
	}
	inode_unlock(tl_inode);

	ret = ocfs2_init_xattr_set_ctxt(inode, di, &xi, &xis,
					&xbs, &ctxt, ref_meta, &credits);
	if (ret) {
		mlog_errno(ret);
		goto cleanup;
	}

	/* we need to update inode's ctime field, so add credit for it. */
	credits += OCFS2_INODE_UPDATE_CREDITS;
	ctxt.handle = ocfs2_start_trans(osb, credits + ref_credits);
	if (IS_ERR(ctxt.handle)) {
		ret = PTR_ERR(ctxt.handle);
		mlog_errno(ret);
		goto out_free_ac;
	}

	ret = __ocfs2_xattr_set_handle(inode, di, &xi, &xis, &xbs, &ctxt);
	ocfs2_update_inode_fsync_trans(ctxt.handle, inode, 0);

	ocfs2_commit_trans(osb, ctxt.handle);

out_free_ac:
	if (ctxt.data_ac)
		ocfs2_free_alloc_context(ctxt.data_ac);
	if (ctxt.meta_ac)
		ocfs2_free_alloc_context(ctxt.meta_ac);
	if (ocfs2_dealloc_has_cluster(&ctxt.dealloc))
		ocfs2_schedule_truncate_log_flush(osb, 1);
	ocfs2_run_deallocs(osb, &ctxt.dealloc);

cleanup:
	if (ref_tree)
		ocfs2_unlock_refcount_tree(osb, ref_tree, 1);
	up_write(&OCFS2_I(inode)->ip_xattr_sem);
	if (!value && !ret) {
		ret = ocfs2_try_remove_refcount_tree(inode, di_bh);
		if (ret)
			mlog_errno(ret);
	}
	ocfs2_inode_unlock_tracker(inode, 1, &oh, had_lock);
cleanup_nolock:
	brelse(di_bh);
	brelse(xbs.xattr_bh);
	ocfs2_xattr_bucket_free(xbs.bucket);

	return ret;
}