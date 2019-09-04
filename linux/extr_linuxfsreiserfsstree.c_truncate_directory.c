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
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; } ;
struct inode {int /*<<< orphan*/  i_sb; scalar_t__ i_nlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DOT_OFFSET ; 
 int /*<<< orphan*/  INODE_PKEY (struct inode*) ; 
 int /*<<< orphan*/  KEY_FORMAT_3_5 ; 
 int /*<<< orphan*/  SD_OFFSET ; 
 int /*<<< orphan*/  TYPE_DIRENTRY ; 
 int /*<<< orphan*/  TYPE_STAT_DATA ; 
 int /*<<< orphan*/  reiserfs_delete_solid_item (struct reiserfs_transaction_handle*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_error (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  reiserfs_update_sd (struct reiserfs_transaction_handle*,struct inode*) ; 
 int /*<<< orphan*/  set_le_key_k_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_le_key_k_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void truncate_directory(struct reiserfs_transaction_handle *th,
			       struct inode *inode)
{
	BUG_ON(!th->t_trans_id);
	if (inode->i_nlink)
		reiserfs_error(inode->i_sb, "vs-5655", "link count != 0");

	set_le_key_k_offset(KEY_FORMAT_3_5, INODE_PKEY(inode), DOT_OFFSET);
	set_le_key_k_type(KEY_FORMAT_3_5, INODE_PKEY(inode), TYPE_DIRENTRY);
	reiserfs_delete_solid_item(th, inode, INODE_PKEY(inode));
	reiserfs_update_sd(th, inode);
	set_le_key_k_offset(KEY_FORMAT_3_5, INODE_PKEY(inode), SD_OFFSET);
	set_le_key_k_type(KEY_FORMAT_3_5, INODE_PKEY(inode), TYPE_STAT_DATA);
}