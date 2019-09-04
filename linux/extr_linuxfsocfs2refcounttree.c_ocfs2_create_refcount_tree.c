#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ocfs2_super {int fs_generation; int /*<<< orphan*/  osb_lock; int /*<<< orphan*/  s_next_generation; int /*<<< orphan*/  sb; } ;
struct ocfs2_refcount_tree {scalar_t__ rf_generation; int /*<<< orphan*/  rf_ci; } ;
struct TYPE_4__ {void* rl_count; } ;
struct ocfs2_refcount_block {scalar_t__ rf_generation; TYPE_1__ rf_records; void* rf_count; void* rf_blkno; void* rf_fs_generation; void* rf_suballoc_bit; void* rf_suballoc_loc; void* rf_suballoc_slot; } ;
struct ocfs2_inode_info {int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_dyn_features; scalar_t__ ip_blkno; } ;
struct ocfs2_dinode {void* i_refcount_loc; void* i_dyn_features; } ;
struct ocfs2_alloc_context {int /*<<< orphan*/  ac_alloc_slot; } ;
struct inode {TYPE_2__* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_5__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_HAS_REFCOUNT_FL ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_CREATE ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  OCFS2_REFCOUNT_BLOCK_SIGNATURE ; 
 int /*<<< orphan*/  OCFS2_REFCOUNT_TREE_CREATE_CREDITS ; 
 struct ocfs2_super* OCFS2_SB (TYPE_2__*) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_refcount_tree*) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct ocfs2_refcount_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 struct ocfs2_refcount_tree* ocfs2_allocate_refcount_tree (struct ocfs2_super*,scalar_t__) ; 
 int ocfs2_claim_metadata (int /*<<< orphan*/ *,struct ocfs2_alloc_context*,int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_erase_refcount_tree_from_list_no_lock (struct ocfs2_super*,struct ocfs2_refcount_tree*) ; 
 struct ocfs2_refcount_tree* ocfs2_find_refcount_tree (struct ocfs2_super*,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_init_refcount_tree_lock (struct ocfs2_super*,struct ocfs2_refcount_tree*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_insert_refcount_tree (struct ocfs2_super*,struct ocfs2_refcount_tree*) ; 
 int /*<<< orphan*/  ocfs2_is_refcount_inode (struct inode*) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_rb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_refcount_recs_per_rb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_refcount_tree_put (struct ocfs2_refcount_tree*) ; 
 int ocfs2_reserve_new_metadata_blocks (struct ocfs2_super*,int,struct ocfs2_alloc_context**) ; 
 int /*<<< orphan*/  ocfs2_set_new_buffer_uptodate (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_getblk (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocfs2_create_refcount_tree (unsigned long long) ; 
 int /*<<< orphan*/  trace_ocfs2_create_refcount_tree_blkno (unsigned long long) ; 

__attribute__((used)) static int ocfs2_create_refcount_tree(struct inode *inode,
				      struct buffer_head *di_bh)
{
	int ret;
	handle_t *handle = NULL;
	struct ocfs2_alloc_context *meta_ac = NULL;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)di_bh->b_data;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct buffer_head *new_bh = NULL;
	struct ocfs2_refcount_block *rb;
	struct ocfs2_refcount_tree *new_tree = NULL, *tree = NULL;
	u16 suballoc_bit_start;
	u32 num_got;
	u64 suballoc_loc, first_blkno;

	BUG_ON(ocfs2_is_refcount_inode(inode));

	trace_ocfs2_create_refcount_tree(
		(unsigned long long)oi->ip_blkno);

	ret = ocfs2_reserve_new_metadata_blocks(osb, 1, &meta_ac);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	handle = ocfs2_start_trans(osb, OCFS2_REFCOUNT_TREE_CREATE_CREDITS);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	ret = ocfs2_claim_metadata(handle, meta_ac, 1, &suballoc_loc,
				   &suballoc_bit_start, &num_got,
				   &first_blkno);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	new_tree = ocfs2_allocate_refcount_tree(osb, first_blkno);
	if (!new_tree) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out_commit;
	}

	new_bh = sb_getblk(inode->i_sb, first_blkno);
	if (!new_bh) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out_commit;
	}
	ocfs2_set_new_buffer_uptodate(&new_tree->rf_ci, new_bh);

	ret = ocfs2_journal_access_rb(handle, &new_tree->rf_ci, new_bh,
				      OCFS2_JOURNAL_ACCESS_CREATE);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	/* Initialize ocfs2_refcount_block. */
	rb = (struct ocfs2_refcount_block *)new_bh->b_data;
	memset(rb, 0, inode->i_sb->s_blocksize);
	strcpy((void *)rb, OCFS2_REFCOUNT_BLOCK_SIGNATURE);
	rb->rf_suballoc_slot = cpu_to_le16(meta_ac->ac_alloc_slot);
	rb->rf_suballoc_loc = cpu_to_le64(suballoc_loc);
	rb->rf_suballoc_bit = cpu_to_le16(suballoc_bit_start);
	rb->rf_fs_generation = cpu_to_le32(osb->fs_generation);
	rb->rf_blkno = cpu_to_le64(first_blkno);
	rb->rf_count = cpu_to_le32(1);
	rb->rf_records.rl_count =
			cpu_to_le16(ocfs2_refcount_recs_per_rb(osb->sb));
	spin_lock(&osb->osb_lock);
	rb->rf_generation = osb->s_next_generation++;
	spin_unlock(&osb->osb_lock);

	ocfs2_journal_dirty(handle, new_bh);

	spin_lock(&oi->ip_lock);
	oi->ip_dyn_features |= OCFS2_HAS_REFCOUNT_FL;
	di->i_dyn_features = cpu_to_le16(oi->ip_dyn_features);
	di->i_refcount_loc = cpu_to_le64(first_blkno);
	spin_unlock(&oi->ip_lock);

	trace_ocfs2_create_refcount_tree_blkno((unsigned long long)first_blkno);

	ocfs2_journal_dirty(handle, di_bh);

	/*
	 * We have to init the tree lock here since it will use
	 * the generation number to create it.
	 */
	new_tree->rf_generation = le32_to_cpu(rb->rf_generation);
	ocfs2_init_refcount_tree_lock(osb, new_tree, first_blkno,
				      new_tree->rf_generation);

	spin_lock(&osb->osb_lock);
	tree = ocfs2_find_refcount_tree(osb, first_blkno);

	/*
	 * We've just created a new refcount tree in this block.  If
	 * we found a refcount tree on the ocfs2_super, it must be
	 * one we just deleted.  We free the old tree before
	 * inserting the new tree.
	 */
	BUG_ON(tree && tree->rf_generation == new_tree->rf_generation);
	if (tree)
		ocfs2_erase_refcount_tree_from_list_no_lock(osb, tree);
	ocfs2_insert_refcount_tree(osb, new_tree);
	spin_unlock(&osb->osb_lock);
	new_tree = NULL;
	if (tree)
		ocfs2_refcount_tree_put(tree);

out_commit:
	ocfs2_commit_trans(osb, handle);

out:
	if (new_tree) {
		ocfs2_metadata_cache_exit(&new_tree->rf_ci);
		kfree(new_tree);
	}

	brelse(new_bh);
	if (meta_ac)
		ocfs2_free_alloc_context(meta_ac);

	return ret;
}