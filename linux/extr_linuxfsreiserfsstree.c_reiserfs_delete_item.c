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
struct treepath {int dummy; } ;
struct tree_balance {int* insert_size; } ;
struct super_block {int s_blocksize; } ;
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; } ;
struct item_head {int dummy; } ;
struct inode {struct super_block* i_sb; int /*<<< orphan*/  i_mode; } ;
struct cpu_key {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CARRY_ON ; 
 int FILE_NOT_FOUND ; 
 int IO_ERROR ; 
 scalar_t__ M_DELETE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PATH_PLAST_BUFFER (struct treepath*) ; 
 int /*<<< orphan*/  PROC_INFO_INC (struct super_block*,int /*<<< orphan*/ ) ; 
 int REPEAT_SEARCH ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int UNFM_P_SIZE ; 
 int calc_deleted_bytes_number (struct tree_balance*,scalar_t__) ; 
 int /*<<< orphan*/  copy_item_head (struct item_head*,struct item_head*) ; 
 int /*<<< orphan*/  delete_item_restarted ; 
 int /*<<< orphan*/  do_balance (struct tree_balance*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dquot_free_space_nodirty (struct inode*,int) ; 
 int fix_nodes (scalar_t__,struct tree_balance*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ih_item_body (int /*<<< orphan*/ ,struct item_head*) ; 
 int ih_item_len (struct item_head*) ; 
 int /*<<< orphan*/  init_tb_struct (struct reiserfs_transaction_handle*,struct tree_balance*,struct super_block*,struct treepath*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_direct_le_ih (struct item_head*) ; 
 char* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (char*) ; 
 int le_ih_k_offset (struct item_head*) ; 
 int /*<<< orphan*/  max_reiserfs_offset (struct inode*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mode ; 
 int /*<<< orphan*/  prepare_for_delete_or_cut (struct reiserfs_transaction_handle*,struct inode*,struct treepath*,struct cpu_key const*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*,struct cpu_key const*) ; 
 int /*<<< orphan*/  reiserfs_write_lock_nested (struct super_block*,int) ; 
 int reiserfs_write_unlock_nested (struct super_block*) ; 
 int search_for_position_by_key (struct super_block*,struct cpu_key const*,struct treepath*) ; 
 struct item_head* tp_item_head (struct treepath*) ; 
 int /*<<< orphan*/  unfix_nodes (struct tree_balance*) ; 

int reiserfs_delete_item(struct reiserfs_transaction_handle *th,
			 struct treepath *path, const struct cpu_key *item_key,
			 struct inode *inode, struct buffer_head *un_bh)
{
	struct super_block *sb = inode->i_sb;
	struct tree_balance s_del_balance;
	struct item_head s_ih;
	struct item_head *q_ih;
	int quota_cut_bytes;
	int ret_value, del_size, removed;
	int depth;

#ifdef CONFIG_REISERFS_CHECK
	char mode;
	int iter = 0;
#endif

	BUG_ON(!th->t_trans_id);

	init_tb_struct(th, &s_del_balance, sb, path,
		       0 /*size is unknown */ );

	while (1) {
		removed = 0;

#ifdef CONFIG_REISERFS_CHECK
		iter++;
		mode =
#endif
		    prepare_for_delete_or_cut(th, inode, path,
					      item_key, &removed,
					      &del_size,
					      max_reiserfs_offset(inode));

		RFALSE(mode != M_DELETE, "PAP-5320: mode must be M_DELETE");

		copy_item_head(&s_ih, tp_item_head(path));
		s_del_balance.insert_size[0] = del_size;

		ret_value = fix_nodes(M_DELETE, &s_del_balance, NULL, NULL);
		if (ret_value != REPEAT_SEARCH)
			break;

		PROC_INFO_INC(sb, delete_item_restarted);

		/* file system changed, repeat search */
		ret_value =
		    search_for_position_by_key(sb, item_key, path);
		if (ret_value == IO_ERROR)
			break;
		if (ret_value == FILE_NOT_FOUND) {
			reiserfs_warning(sb, "vs-5340",
					 "no items of the file %K found",
					 item_key);
			break;
		}
	}			/* while (1) */

	if (ret_value != CARRY_ON) {
		unfix_nodes(&s_del_balance);
		return 0;
	}

	/* reiserfs_delete_item returns item length when success */
	ret_value = calc_deleted_bytes_number(&s_del_balance, M_DELETE);
	q_ih = tp_item_head(path);
	quota_cut_bytes = ih_item_len(q_ih);

	/*
	 * hack so the quota code doesn't have to guess if the file has a
	 * tail.  On tail insert, we allocate quota for 1 unformatted node.
	 * We test the offset because the tail might have been
	 * split into multiple items, and we only want to decrement for
	 * the unfm node once
	 */
	if (!S_ISLNK(inode->i_mode) && is_direct_le_ih(q_ih)) {
		if ((le_ih_k_offset(q_ih) & (sb->s_blocksize - 1)) == 1) {
			quota_cut_bytes = sb->s_blocksize + UNFM_P_SIZE;
		} else {
			quota_cut_bytes = 0;
		}
	}

	if (un_bh) {
		int off;
		char *data;

		/*
		 * We are in direct2indirect conversion, so move tail contents
		 * to the unformatted node
		 */
		/*
		 * note, we do the copy before preparing the buffer because we
		 * don't care about the contents of the unformatted node yet.
		 * the only thing we really care about is the direct item's
		 * data is in the unformatted node.
		 *
		 * Otherwise, we would have to call
		 * reiserfs_prepare_for_journal on the unformatted node,
		 * which might schedule, meaning we'd have to loop all the
		 * way back up to the start of the while loop.
		 *
		 * The unformatted node must be dirtied later on.  We can't be
		 * sure here if the entire tail has been deleted yet.
		 *
		 * un_bh is from the page cache (all unformatted nodes are
		 * from the page cache) and might be a highmem page.  So, we
		 * can't use un_bh->b_data.
		 * -clm
		 */

		data = kmap_atomic(un_bh->b_page);
		off = ((le_ih_k_offset(&s_ih) - 1) & (PAGE_SIZE - 1));
		memcpy(data + off,
		       ih_item_body(PATH_PLAST_BUFFER(path), &s_ih),
		       ret_value);
		kunmap_atomic(data);
	}

	/* Perform balancing after all resources have been collected at once. */
	do_balance(&s_del_balance, NULL, NULL, M_DELETE);

#ifdef REISERQUOTA_DEBUG
	reiserfs_debug(sb, REISERFS_DEBUG_CODE,
		       "reiserquota delete_item(): freeing %u, id=%u type=%c",
		       quota_cut_bytes, inode->i_uid, head2type(&s_ih));
#endif
	depth = reiserfs_write_unlock_nested(inode->i_sb);
	dquot_free_space_nodirty(inode, quota_cut_bytes);
	reiserfs_write_lock_nested(inode->i_sb, depth);

	/* Return deleted body length */
	return ret_value;
}