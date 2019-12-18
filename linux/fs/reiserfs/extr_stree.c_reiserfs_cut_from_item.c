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
struct treepath {int dummy; } ;
struct tree_balance {int* insert_size; struct treepath* tb_path; } ;
struct super_block {int s_blocksize; } ;
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; } ;
struct page {int dummy; } ;
struct item_head {int dummy; } ;
struct inode {int /*<<< orphan*/  i_uid; struct super_block* i_sb; int /*<<< orphan*/  i_mode; } ;
struct cpu_key {int key_length; } ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_first_direct_byte; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CARRY_ON ; 
 int EIO ; 
 int ENOENT ; 
 int IO_ERROR ; 
 char M_CONVERT ; 
 char M_CUT ; 
 char M_DELETE ; 
 char M_INSERT ; 
 char M_PASTE ; 
 char M_SKIP_BALANCING ; 
 int NO_DISK_SPACE ; 
 scalar_t__ PATH_LAST_POSITION (struct treepath*) ; 
 int /*<<< orphan*/  PATH_PLAST_BUFFER (struct treepath*) ; 
 int POSITION_FOUND ; 
 int POSITION_NOT_FOUND ; 
 int /*<<< orphan*/  PROC_INFO_INC (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REISERFS_DEBUG_CODE ; 
 TYPE_1__* REISERFS_I (struct inode*) ; 
 int REPEAT_SEARCH ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_INDIRECT ; 
 int /*<<< orphan*/  U32_MAX ; 
 int UNFM_P_SIZE ; 
 int calc_deleted_bytes_number (struct tree_balance*,char) ; 
 int /*<<< orphan*/  cut_from_item_restarted ; 
 int /*<<< orphan*/  do_balance (struct tree_balance*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  dquot_free_space_nodirty (struct inode*,int) ; 
 int fix_nodes (char,struct tree_balance*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i_pack_on_close_mask ; 
 int ih_item_len (struct item_head*) ; 
 int /*<<< orphan*/  indirect_to_direct_roll_back (struct reiserfs_transaction_handle*,struct inode*,struct treepath*) ; 
 int /*<<< orphan*/  init_tb_struct (struct reiserfs_transaction_handle*,struct tree_balance*,struct super_block*,struct treepath*,int) ; 
 scalar_t__ is_direct_le_ih (struct item_head*) ; 
 int /*<<< orphan*/  is_indirect_le_ih (struct item_head*) ; 
 int le_ih_k_offset (struct item_head*) ; 
 int maybe_indirect_to_direct (struct reiserfs_transaction_handle*,struct inode*,struct page*,struct treepath*,struct cpu_key*,int,char*) ; 
 int /*<<< orphan*/  pathrelse (struct treepath*) ; 
 char prepare_for_delete_or_cut (struct reiserfs_transaction_handle*,struct inode*,struct treepath*,struct cpu_key*,int*,int*,int) ; 
 int /*<<< orphan*/  print_block (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  reiserfs_debug (struct super_block*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  reiserfs_panic (struct super_block*,char*,char*,struct cpu_key*,...) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*,...) ; 
 int /*<<< orphan*/  reiserfs_write_lock_nested (struct super_block*,int) ; 
 int reiserfs_write_unlock_nested (struct super_block*) ; 
 int search_for_position_by_key (struct super_block*,struct cpu_key*,struct treepath*) ; 
 int /*<<< orphan*/  set_cpu_key_k_offset (struct cpu_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpu_key_k_type (struct cpu_key*,int /*<<< orphan*/ ) ; 
 struct item_head* tp_item_head (struct treepath*) ; 
 int /*<<< orphan*/  unfix_nodes (struct tree_balance*) ; 
 int /*<<< orphan*/  unmap_buffers (struct page*,int) ; 

int reiserfs_cut_from_item(struct reiserfs_transaction_handle *th,
			   struct treepath *path,
			   struct cpu_key *item_key,
			   struct inode *inode,
			   struct page *page, loff_t new_file_size)
{
	struct super_block *sb = inode->i_sb;
	/*
	 * Every function which is going to call do_balance must first
	 * create a tree_balance structure.  Then it must fill up this
	 * structure by using the init_tb_struct and fix_nodes functions.
	 * After that we can make tree balancing.
	 */
	struct tree_balance s_cut_balance;
	struct item_head *p_le_ih;
	int cut_size = 0;	/* Amount to be cut. */
	int ret_value = CARRY_ON;
	int removed = 0;	/* Number of the removed unformatted nodes. */
	int is_inode_locked = 0;
	char mode;		/* Mode of the balance. */
	int retval2 = -1;
	int quota_cut_bytes;
	loff_t tail_pos = 0;
	int depth;

	BUG_ON(!th->t_trans_id);

	init_tb_struct(th, &s_cut_balance, inode->i_sb, path,
		       cut_size);

	/*
	 * Repeat this loop until we either cut the item without needing
	 * to balance, or we fix_nodes without schedule occurring
	 */
	while (1) {
		/*
		 * Determine the balance mode, position of the first byte to
		 * be cut, and size to be cut.  In case of the indirect item
		 * free unformatted nodes which are pointed to by the cut
		 * pointers.
		 */

		mode =
		    prepare_for_delete_or_cut(th, inode, path,
					      item_key, &removed,
					      &cut_size, new_file_size);
		if (mode == M_CONVERT) {
			/*
			 * convert last unformatted node to direct item or
			 * leave tail in the unformatted node
			 */
			RFALSE(ret_value != CARRY_ON,
			       "PAP-5570: can not convert twice");

			ret_value =
			    maybe_indirect_to_direct(th, inode, page,
						     path, item_key,
						     new_file_size, &mode);
			if (mode == M_SKIP_BALANCING)
				/* tail has been left in the unformatted node */
				return ret_value;

			is_inode_locked = 1;

			/*
			 * removing of last unformatted node will
			 * change value we have to return to truncate.
			 * Save it
			 */
			retval2 = ret_value;

			/*
			 * So, we have performed the first part of the
			 * conversion:
			 * inserting the new direct item.  Now we are
			 * removing the last unformatted node pointer.
			 * Set key to search for it.
			 */
			set_cpu_key_k_type(item_key, TYPE_INDIRECT);
			item_key->key_length = 4;
			new_file_size -=
			    (new_file_size & (sb->s_blocksize - 1));
			tail_pos = new_file_size;
			set_cpu_key_k_offset(item_key, new_file_size + 1);
			if (search_for_position_by_key
			    (sb, item_key,
			     path) == POSITION_NOT_FOUND) {
				print_block(PATH_PLAST_BUFFER(path), 3,
					    PATH_LAST_POSITION(path) - 1,
					    PATH_LAST_POSITION(path) + 1);
				reiserfs_panic(sb, "PAP-5580", "item to "
					       "convert does not exist (%K)",
					       item_key);
			}
			continue;
		}
		if (cut_size == 0) {
			pathrelse(path);
			return 0;
		}

		s_cut_balance.insert_size[0] = cut_size;

		ret_value = fix_nodes(mode, &s_cut_balance, NULL, NULL);
		if (ret_value != REPEAT_SEARCH)
			break;

		PROC_INFO_INC(sb, cut_from_item_restarted);

		ret_value =
		    search_for_position_by_key(sb, item_key, path);
		if (ret_value == POSITION_FOUND)
			continue;

		reiserfs_warning(sb, "PAP-5610", "item %K not found",
				 item_key);
		unfix_nodes(&s_cut_balance);
		return (ret_value == IO_ERROR) ? -EIO : -ENOENT;
	}			/* while */

	/* check fix_nodes results (IO_ERROR or NO_DISK_SPACE) */
	if (ret_value != CARRY_ON) {
		if (is_inode_locked) {
			/*
			 * FIXME: this seems to be not needed: we are always
			 * able to cut item
			 */
			indirect_to_direct_roll_back(th, inode, path);
		}
		if (ret_value == NO_DISK_SPACE)
			reiserfs_warning(sb, "reiserfs-5092",
					 "NO_DISK_SPACE");
		unfix_nodes(&s_cut_balance);
		return -EIO;
	}

	/* go ahead and perform balancing */

	RFALSE(mode == M_PASTE || mode == M_INSERT, "invalid mode");

	/* Calculate number of bytes that need to be cut from the item. */
	quota_cut_bytes =
	    (mode ==
	     M_DELETE) ? ih_item_len(tp_item_head(path)) : -s_cut_balance.
	    insert_size[0];
	if (retval2 == -1)
		ret_value = calc_deleted_bytes_number(&s_cut_balance, mode);
	else
		ret_value = retval2;

	/*
	 * For direct items, we only change the quota when deleting the last
	 * item.
	 */
	p_le_ih = tp_item_head(s_cut_balance.tb_path);
	if (!S_ISLNK(inode->i_mode) && is_direct_le_ih(p_le_ih)) {
		if (mode == M_DELETE &&
		    (le_ih_k_offset(p_le_ih) & (sb->s_blocksize - 1)) ==
		    1) {
			/* FIXME: this is to keep 3.5 happy */
			REISERFS_I(inode)->i_first_direct_byte = U32_MAX;
			quota_cut_bytes = sb->s_blocksize + UNFM_P_SIZE;
		} else {
			quota_cut_bytes = 0;
		}
	}
#ifdef CONFIG_REISERFS_CHECK
	if (is_inode_locked) {
		struct item_head *le_ih =
		    tp_item_head(s_cut_balance.tb_path);
		/*
		 * we are going to complete indirect2direct conversion. Make
		 * sure, that we exactly remove last unformatted node pointer
		 * of the item
		 */
		if (!is_indirect_le_ih(le_ih))
			reiserfs_panic(sb, "vs-5652",
				       "item must be indirect %h", le_ih);

		if (mode == M_DELETE && ih_item_len(le_ih) != UNFM_P_SIZE)
			reiserfs_panic(sb, "vs-5653", "completing "
				       "indirect2direct conversion indirect "
				       "item %h being deleted must be of "
				       "4 byte long", le_ih);

		if (mode == M_CUT
		    && s_cut_balance.insert_size[0] != -UNFM_P_SIZE) {
			reiserfs_panic(sb, "vs-5654", "can not complete "
				       "indirect2direct conversion of %h "
				       "(CUT, insert_size==%d)",
				       le_ih, s_cut_balance.insert_size[0]);
		}
		/*
		 * it would be useful to make sure, that right neighboring
		 * item is direct item of this file
		 */
	}
#endif

	do_balance(&s_cut_balance, NULL, NULL, mode);
	if (is_inode_locked) {
		/*
		 * we've done an indirect->direct conversion.  when the
		 * data block was freed, it was removed from the list of
		 * blocks that must be flushed before the transaction
		 * commits, make sure to unmap and invalidate it
		 */
		unmap_buffers(page, tail_pos);
		REISERFS_I(inode)->i_flags &= ~i_pack_on_close_mask;
	}
#ifdef REISERQUOTA_DEBUG
	reiserfs_debug(inode->i_sb, REISERFS_DEBUG_CODE,
		       "reiserquota cut_from_item(): freeing %u id=%u type=%c",
		       quota_cut_bytes, inode->i_uid, '?');
#endif
	depth = reiserfs_write_unlock_nested(sb);
	dquot_free_space_nodirty(inode, quota_cut_bytes);
	reiserfs_write_lock_nested(sb, depth);
	return ret_value;
}