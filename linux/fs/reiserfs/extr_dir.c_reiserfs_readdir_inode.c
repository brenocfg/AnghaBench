#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct reiserfs_key {int dummy; } ;
struct reiserfs_dir_entry {int de_entry_num; int de_item_num; struct item_head* de_ih; struct buffer_head* de_bh; } ;
struct reiserfs_de_head {int dummy; } ;
struct item_head {struct reiserfs_key const ih_key; } ;
struct inode {TYPE_1__* i_sb; } ;
struct dir_context {void* pos; } ;
struct cpu_key {int dummy; } ;
struct buffer_head {char* b_data; int b_size; } ;
typedef  void* loff_t ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_16__ {int /*<<< orphan*/  reada; } ;
struct TYPE_15__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 struct reiserfs_de_head* B_I_DEH (struct buffer_head*,struct item_head*) ; 
 char* B_I_DEH_ENTRY_FILE_NAME (struct buffer_head*,struct item_head*,struct reiserfs_de_head*) ; 
 int B_NR_ITEMS (struct buffer_head*) ; 
 scalar_t__ COMP_SHORT_KEYS (struct reiserfs_key const*,struct cpu_key*) ; 
 int /*<<< orphan*/  DOT_OFFSET ; 
 int /*<<< orphan*/  DT_UNKNOWN ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INITIALIZE_PATH (TYPE_2__) ; 
 int IO_ERROR ; 
 int /*<<< orphan*/  KEY_FORMAT_3_5 ; 
 int /*<<< orphan*/  MIN_KEY ; 
 int /*<<< orphan*/  PATH_READA ; 
 int POSITION_FOUND ; 
 int REISERFS_MAX_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*,...) ; 
 int /*<<< orphan*/  TYPE_DIRENTRY ; 
 int /*<<< orphan*/  comp_le_keys (struct reiserfs_key const*,int /*<<< orphan*/ *) ; 
 void* cpu_key_k_offset (struct cpu_key*) ; 
 int /*<<< orphan*/  de_visible (struct reiserfs_de_head*) ; 
 int /*<<< orphan*/  deh_objectid (struct reiserfs_de_head*) ; 
 void* deh_offset (struct reiserfs_de_head*) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int entry_length (struct buffer_head*,struct item_head*,int) ; 
 struct reiserfs_key* get_rkey (TYPE_2__*,TYPE_1__*) ; 
 int ih_entry_count (struct item_head*) ; 
 scalar_t__ is_privroot_deh (struct inode*,struct reiserfs_de_head*) ; 
 scalar_t__ item_moved (struct item_head*,TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* le_key_k_offset (int /*<<< orphan*/ ,struct reiserfs_key const*) ; 
 int /*<<< orphan*/  make_cpu_key (struct cpu_key*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 TYPE_2__ path_to_entry ; 
 int /*<<< orphan*/  pathrelse (TYPE_2__*) ; 
 int /*<<< orphan*/  reiserfs_check_lock_depth (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  reiserfs_check_path (TYPE_2__*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  reiserfs_write_lock_nested (TYPE_1__*,int) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (TYPE_1__*) ; 
 int reiserfs_write_unlock_nested (TYPE_1__*) ; 
 int search_by_entry_key (TYPE_1__*,struct cpu_key*,TYPE_2__*,struct reiserfs_dir_entry*) ; 
 int /*<<< orphan*/  set_cpu_key_k_offset (struct cpu_key*,void*) ; 
 int /*<<< orphan*/  store_ih (struct item_head*,struct item_head*) ; 
 int strlen (char*) ; 

int reiserfs_readdir_inode(struct inode *inode, struct dir_context *ctx)
{

	/* key of current position in the directory (key of directory entry) */
	struct cpu_key pos_key;

	INITIALIZE_PATH(path_to_entry);
	struct buffer_head *bh;
	int item_num, entry_num;
	const struct reiserfs_key *rkey;
	struct item_head *ih, tmp_ih;
	int search_res;
	char *local_buf;
	loff_t next_pos;
	char small_buf[32];	/* avoid kmalloc if we can */
	struct reiserfs_dir_entry de;
	int ret = 0;
	int depth;

	reiserfs_write_lock(inode->i_sb);

	reiserfs_check_lock_depth(inode->i_sb, "readdir");

	/*
	 * form key for search the next directory entry using
	 * f_pos field of file structure
	 */
	make_cpu_key(&pos_key, inode, ctx->pos ?: DOT_OFFSET, TYPE_DIRENTRY, 3);
	next_pos = cpu_key_k_offset(&pos_key);

	path_to_entry.reada = PATH_READA;
	while (1) {
research:
		/*
		 * search the directory item, containing entry with
		 * specified key
		 */
		search_res =
		    search_by_entry_key(inode->i_sb, &pos_key, &path_to_entry,
					&de);
		if (search_res == IO_ERROR) {
			/*
			 * FIXME: we could just skip part of directory
			 * which could not be read
			 */
			ret = -EIO;
			goto out;
		}
		entry_num = de.de_entry_num;
		bh = de.de_bh;
		item_num = de.de_item_num;
		ih = de.de_ih;
		store_ih(&tmp_ih, ih);

		/* we must have found item, that is item of this directory, */
		RFALSE(COMP_SHORT_KEYS(&ih->ih_key, &pos_key),
		       "vs-9000: found item %h does not match to dir we readdir %K",
		       ih, &pos_key);
		RFALSE(item_num > B_NR_ITEMS(bh) - 1,
		       "vs-9005 item_num == %d, item amount == %d",
		       item_num, B_NR_ITEMS(bh));

		/*
		 * and entry must be not more than number of entries
		 * in the item
		 */
		RFALSE(ih_entry_count(ih) < entry_num,
		       "vs-9010: entry number is too big %d (%d)",
		       entry_num, ih_entry_count(ih));

		/*
		 * go through all entries in the directory item beginning
		 * from the entry, that has been found
		 */
		if (search_res == POSITION_FOUND
		    || entry_num < ih_entry_count(ih)) {
			struct reiserfs_de_head *deh =
			    B_I_DEH(bh, ih) + entry_num;

			for (; entry_num < ih_entry_count(ih);
			     entry_num++, deh++) {
				int d_reclen;
				char *d_name;
				ino_t d_ino;
				loff_t cur_pos = deh_offset(deh);

				/* it is hidden entry */
				if (!de_visible(deh))
					continue;
				d_reclen = entry_length(bh, ih, entry_num);
				d_name = B_I_DEH_ENTRY_FILE_NAME(bh, ih, deh);

				if (d_reclen <= 0 ||
				    d_name + d_reclen > bh->b_data + bh->b_size) {
					/*
					 * There is corrupted data in entry,
					 * We'd better stop here
					 */
					pathrelse(&path_to_entry);
					ret = -EIO;
					goto out;
				}

				if (!d_name[d_reclen - 1])
					d_reclen = strlen(d_name);

				/* too big to send back to VFS */
				if (d_reclen >
				    REISERFS_MAX_NAME(inode->i_sb->
						      s_blocksize)) {
					continue;
				}

				/* Ignore the .reiserfs_priv entry */
				if (is_privroot_deh(inode, deh))
					continue;

				ctx->pos = deh_offset(deh);
				d_ino = deh_objectid(deh);
				if (d_reclen <= 32) {
					local_buf = small_buf;
				} else {
					local_buf = kmalloc(d_reclen,
							    GFP_NOFS);
					if (!local_buf) {
						pathrelse(&path_to_entry);
						ret = -ENOMEM;
						goto out;
					}
					if (item_moved(&tmp_ih, &path_to_entry)) {
						kfree(local_buf);
						goto research;
					}
				}

				/*
				 * Note, that we copy name to user space via
				 * temporary buffer (local_buf) because
				 * filldir will block if user space buffer is
				 * swapped out. At that time entry can move to
				 * somewhere else
				 */
				memcpy(local_buf, d_name, d_reclen);

				/*
				 * Since filldir might sleep, we can release
				 * the write lock here for other waiters
				 */
				depth = reiserfs_write_unlock_nested(inode->i_sb);
				if (!dir_emit
				    (ctx, local_buf, d_reclen, d_ino,
				     DT_UNKNOWN)) {
					reiserfs_write_lock_nested(inode->i_sb, depth);
					if (local_buf != small_buf) {
						kfree(local_buf);
					}
					goto end;
				}
				reiserfs_write_lock_nested(inode->i_sb, depth);
				if (local_buf != small_buf) {
					kfree(local_buf);
				}

				/* deh_offset(deh) may be invalid now. */
				next_pos = cur_pos + 1;

				if (item_moved(&tmp_ih, &path_to_entry)) {
					set_cpu_key_k_offset(&pos_key,
							     next_pos);
					goto research;
				}
			}	/* for */
		}

		/* end of directory has been reached */
		if (item_num != B_NR_ITEMS(bh) - 1)
			goto end;

		/*
		 * item we went through is last item of node. Using right
		 * delimiting key check is it directory end
		 */
		rkey = get_rkey(&path_to_entry, inode->i_sb);
		if (!comp_le_keys(rkey, &MIN_KEY)) {
			/*
			 * set pos_key to key, that is the smallest and greater
			 * that key of the last entry in the item
			 */
			set_cpu_key_k_offset(&pos_key, next_pos);
			continue;
		}

		/* end of directory has been reached */
		if (COMP_SHORT_KEYS(rkey, &pos_key)) {
			goto end;
		}

		/* directory continues in the right neighboring block */
		set_cpu_key_k_offset(&pos_key,
				     le_key_k_offset(KEY_FORMAT_3_5, rkey));

	}			/* while */

end:
	ctx->pos = next_pos;
	pathrelse(&path_to_entry);
	reiserfs_check_path(&path_to_entry);
out:
	reiserfs_write_unlock(inode->i_sb);
	return ret;
}