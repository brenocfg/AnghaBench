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
struct super_block {int s_blocksize; } ;
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; } ;
struct item_head {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct cpu_key {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  pos_in_item ;
typedef  scalar_t__ __u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IH_SIZE ; 
 int I_UNFM_NUM (struct item_head*) ; 
 scalar_t__ JOURNAL_FOR_FREE_BLOCK_AND_UPDATE_SD ; 
 int M_CONVERT ; 
 int M_CUT ; 
 char M_DELETE ; 
 struct buffer_head* PATH_PLAST_BUFFER (struct treepath*) ; 
 scalar_t__ POSITION_FOUND ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 int UNFM_P_SIZE ; 
 int /*<<< orphan*/  copy_item_head (struct item_head*,struct item_head*) ; 
 scalar_t__ get_block_num (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ih_item_body (struct buffer_head*,struct item_head*) ; 
 int ih_item_len (struct item_head*) ; 
 scalar_t__ is_direct_le_ih (struct item_head*) ; 
 scalar_t__ is_direntry_le_ih (struct item_head*) ; 
 scalar_t__ is_statdata_le_ih (struct item_head*) ; 
 scalar_t__ item_moved (struct item_head*,struct treepath*) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,struct buffer_head*) ; 
 int le_ih_k_offset (struct item_head*) ; 
 unsigned long long max_reiserfs_offset (struct inode*) ; 
 char prepare_for_direct_item (struct treepath*,struct item_head*,struct inode*,unsigned long long,int*) ; 
 char prepare_for_direntry_item (struct treepath*,struct item_head*,struct inode*,unsigned long long,int*) ; 
 int /*<<< orphan*/  put_block_num (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_cond_resched (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_free_block (struct reiserfs_transaction_handle*,struct inode*,scalar_t__,int) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (struct super_block*,struct buffer_head*,int) ; 
 int /*<<< orphan*/  reiserfs_restore_prepared_buffer (struct super_block*,struct buffer_head*) ; 
 scalar_t__ reiserfs_transaction_free_space (struct reiserfs_transaction_handle*) ; 
 scalar_t__ search_for_position_by_key (struct super_block*,struct cpu_key const*,struct treepath*) ; 
 struct item_head* tp_item_head (struct treepath*) ; 

__attribute__((used)) static char prepare_for_delete_or_cut(struct reiserfs_transaction_handle *th,
				      struct inode *inode,
				      struct treepath *path,
				      const struct cpu_key *item_key,
				      /*
				       * Number of unformatted nodes
				       * which were removed from end
				       * of the file.
				       */
				      int *removed,
				      int *cut_size,
				      /* MAX_KEY_OFFSET in case of delete. */
				      unsigned long long new_file_length
    )
{
	struct super_block *sb = inode->i_sb;
	struct item_head *p_le_ih = tp_item_head(path);
	struct buffer_head *bh = PATH_PLAST_BUFFER(path);

	BUG_ON(!th->t_trans_id);

	/* Stat_data item. */
	if (is_statdata_le_ih(p_le_ih)) {

		RFALSE(new_file_length != max_reiserfs_offset(inode),
		       "PAP-5210: mode must be M_DELETE");

		*cut_size = -(IH_SIZE + ih_item_len(p_le_ih));
		return M_DELETE;
	}

	/* Directory item. */
	if (is_direntry_le_ih(p_le_ih))
		return prepare_for_direntry_item(path, p_le_ih, inode,
						 new_file_length,
						 cut_size);

	/* Direct item. */
	if (is_direct_le_ih(p_le_ih))
		return prepare_for_direct_item(path, p_le_ih, inode,
					       new_file_length, cut_size);

	/* Case of an indirect item. */
	{
	    int blk_size = sb->s_blocksize;
	    struct item_head s_ih;
	    int need_re_search;
	    int delete = 0;
	    int result = M_CUT;
	    int pos = 0;

	    if ( new_file_length == max_reiserfs_offset (inode) ) {
		/*
		 * prepare_for_delete_or_cut() is called by
		 * reiserfs_delete_item()
		 */
		new_file_length = 0;
		delete = 1;
	    }

	    do {
		need_re_search = 0;
		*cut_size = 0;
		bh = PATH_PLAST_BUFFER(path);
		copy_item_head(&s_ih, tp_item_head(path));
		pos = I_UNFM_NUM(&s_ih);

		while (le_ih_k_offset (&s_ih) + (pos - 1) * blk_size > new_file_length) {
		    __le32 *unfm;
		    __u32 block;

		    /*
		     * Each unformatted block deletion may involve
		     * one additional bitmap block into the transaction,
		     * thereby the initial journal space reservation
		     * might not be enough.
		     */
		    if (!delete && (*cut_size) != 0 &&
			reiserfs_transaction_free_space(th) < JOURNAL_FOR_FREE_BLOCK_AND_UPDATE_SD)
			break;

		    unfm = (__le32 *)ih_item_body(bh, &s_ih) + pos - 1;
		    block = get_block_num(unfm, 0);

		    if (block != 0) {
			reiserfs_prepare_for_journal(sb, bh, 1);
			put_block_num(unfm, 0, 0);
			journal_mark_dirty(th, bh);
			reiserfs_free_block(th, inode, block, 1);
		    }

		    reiserfs_cond_resched(sb);

		    if (item_moved (&s_ih, path))  {
			need_re_search = 1;
			break;
		    }

		    pos --;
		    (*removed)++;
		    (*cut_size) -= UNFM_P_SIZE;

		    if (pos == 0) {
			(*cut_size) -= IH_SIZE;
			result = M_DELETE;
			break;
		    }
		}
		/*
		 * a trick.  If the buffer has been logged, this will
		 * do nothing.  If we've broken the loop without logging
		 * it, it will restore the buffer
		 */
		reiserfs_restore_prepared_buffer(sb, bh);
	    } while (need_re_search &&
		     search_for_position_by_key(sb, item_key, path) == POSITION_FOUND);
	    pos_in_item(path) = pos * UNFM_P_SIZE;

	    if (*cut_size == 0) {
		/*
		 * Nothing was cut. maybe convert last unformatted node to the
		 * direct item?
		 */
		result = M_CONVERT;
	    }
	    return result;
	}
}