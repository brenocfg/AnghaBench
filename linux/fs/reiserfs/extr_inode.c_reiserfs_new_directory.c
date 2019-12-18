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
struct treepath {int dummy; } ;
struct super_block {int dummy; } ;
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; struct super_block* t_super; } ;
struct TYPE_3__ {int /*<<< orphan*/  k_objectid; int /*<<< orphan*/  k_dir_id; } ;
struct item_head {TYPE_1__ ih_key; } ;
struct inode {int dummy; } ;
struct cpu_key {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  k_objectid; int /*<<< orphan*/  k_dir_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DOT_OFFSET ; 
 int EEXIST ; 
 int EIO ; 
 int EMPTY_DIR_SIZE ; 
 int EMPTY_DIR_SIZE_V1 ; 
 TYPE_2__* INODE_PKEY (struct inode*) ; 
 int IO_ERROR ; 
 int ITEM_FOUND ; 
 int /*<<< orphan*/  KEY_FORMAT_3_5 ; 
 int /*<<< orphan*/  TYPE_DIRENTRY ; 
 int /*<<< orphan*/  _make_cpu_key (struct cpu_key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_empty_dir_item (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_empty_dir_item_v1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_le_item_head (struct item_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ old_format_only (struct super_block*) ; 
 int /*<<< orphan*/  pathrelse (struct treepath*) ; 
 int /*<<< orphan*/  reiserfs_error (struct super_block*,char*,char*) ; 
 int reiserfs_insert_item (struct reiserfs_transaction_handle*,struct treepath*,struct cpu_key*,struct item_head*,struct inode*,char*) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*,TYPE_1__*) ; 
 int search_item (struct super_block*,struct cpu_key*,struct treepath*) ; 

__attribute__((used)) static int reiserfs_new_directory(struct reiserfs_transaction_handle *th,
				  struct inode *inode,
				  struct item_head *ih, struct treepath *path,
				  struct inode *dir)
{
	struct super_block *sb = th->t_super;
	char empty_dir[EMPTY_DIR_SIZE];
	char *body = empty_dir;
	struct cpu_key key;
	int retval;

	BUG_ON(!th->t_trans_id);

	_make_cpu_key(&key, KEY_FORMAT_3_5, le32_to_cpu(ih->ih_key.k_dir_id),
		      le32_to_cpu(ih->ih_key.k_objectid), DOT_OFFSET,
		      TYPE_DIRENTRY, 3 /*key length */ );

	/*
	 * compose item head for new item. Directories consist of items of
	 * old type (ITEM_VERSION_1). Do not set key (second arg is 0), it
	 * is done by reiserfs_new_inode
	 */
	if (old_format_only(sb)) {
		make_le_item_head(ih, NULL, KEY_FORMAT_3_5, DOT_OFFSET,
				  TYPE_DIRENTRY, EMPTY_DIR_SIZE_V1, 2);

		make_empty_dir_item_v1(body, ih->ih_key.k_dir_id,
				       ih->ih_key.k_objectid,
				       INODE_PKEY(dir)->k_dir_id,
				       INODE_PKEY(dir)->k_objectid);
	} else {
		make_le_item_head(ih, NULL, KEY_FORMAT_3_5, DOT_OFFSET,
				  TYPE_DIRENTRY, EMPTY_DIR_SIZE, 2);

		make_empty_dir_item(body, ih->ih_key.k_dir_id,
				    ih->ih_key.k_objectid,
				    INODE_PKEY(dir)->k_dir_id,
				    INODE_PKEY(dir)->k_objectid);
	}

	/* look for place in the tree for new item */
	retval = search_item(sb, &key, path);
	if (retval == IO_ERROR) {
		reiserfs_error(sb, "vs-13080",
			       "i/o failure occurred creating new directory");
		return -EIO;
	}
	if (retval == ITEM_FOUND) {
		pathrelse(path);
		reiserfs_warning(sb, "vs-13070",
				 "object with this key exists (%k)",
				 &(ih->ih_key));
		return -EEXIST;
	}

	/* insert item, that is empty directory item */
	return reiserfs_insert_item(th, path, &key, ih, inode, body);
}