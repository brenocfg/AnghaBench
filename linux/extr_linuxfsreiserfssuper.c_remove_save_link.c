#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct reiserfs_transaction_handle {int dummy; } ;
struct reiserfs_key {int /*<<< orphan*/  k_objectid; int /*<<< orphan*/  k_dir_id; } ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct TYPE_6__ {int /*<<< orphan*/  k_objectid; } ;
struct TYPE_5__ {int i_flags; } ;
struct TYPE_4__ {int s_blocksize; } ;

/* Variables and functions */
 TYPE_3__* INODE_PKEY (struct inode*) ; 
 int /*<<< orphan*/  JOURNAL_PER_BALANCE_CNT ; 
 int /*<<< orphan*/  KEY_FORMAT_3_5 ; 
 int /*<<< orphan*/  MAX_KEY_OBJECTID ; 
 TYPE_2__* REISERFS_I (struct inode*) ; 
 int /*<<< orphan*/  TYPE_DIRECT ; 
 int /*<<< orphan*/  TYPE_INDIRECT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int i_link_saved_truncate_mask ; 
 int i_link_saved_unlink_mask ; 
 int journal_begin (struct reiserfs_transaction_handle*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int journal_end (struct reiserfs_transaction_handle*) ; 
 int /*<<< orphan*/  reiserfs_delete_solid_item (struct reiserfs_transaction_handle*,int /*<<< orphan*/ *,struct reiserfs_key*) ; 
 int /*<<< orphan*/  reiserfs_release_objectid (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_le_key_k_offset (int /*<<< orphan*/ ,struct reiserfs_key*,int) ; 
 int /*<<< orphan*/  set_le_key_k_type (int /*<<< orphan*/ ,struct reiserfs_key*,int /*<<< orphan*/ ) ; 

int remove_save_link(struct inode *inode, int truncate)
{
	struct reiserfs_transaction_handle th;
	struct reiserfs_key key;
	int err;

	/* we are going to do one balancing only */
	err = journal_begin(&th, inode->i_sb, JOURNAL_PER_BALANCE_CNT);
	if (err)
		return err;

	/* setup key of "save" link */
	key.k_dir_id = cpu_to_le32(MAX_KEY_OBJECTID);
	key.k_objectid = INODE_PKEY(inode)->k_objectid;
	if (!truncate) {
		/* unlink, rmdir, rename */
		set_le_key_k_offset(KEY_FORMAT_3_5, &key,
				    1 + inode->i_sb->s_blocksize);
		set_le_key_k_type(KEY_FORMAT_3_5, &key, TYPE_DIRECT);
	} else {
		/* truncate */
		set_le_key_k_offset(KEY_FORMAT_3_5, &key, 1);
		set_le_key_k_type(KEY_FORMAT_3_5, &key, TYPE_INDIRECT);
	}

	if ((truncate &&
	     (REISERFS_I(inode)->i_flags & i_link_saved_truncate_mask)) ||
	    (!truncate &&
	     (REISERFS_I(inode)->i_flags & i_link_saved_unlink_mask)))
		/* don't take quota bytes from anywhere */
		reiserfs_delete_solid_item(&th, NULL, &key);
	if (!truncate) {
		reiserfs_release_objectid(&th, inode->i_ino);
		REISERFS_I(inode)->i_flags &= ~i_link_saved_unlink_mask;
	} else
		REISERFS_I(inode)->i_flags &= ~i_link_saved_truncate_mask;

	return journal_end(&th);
}