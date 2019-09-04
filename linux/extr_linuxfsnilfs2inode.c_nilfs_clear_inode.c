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
struct nilfs_inode_info {scalar_t__ i_root; int /*<<< orphan*/  i_btnode_cache; int /*<<< orphan*/  i_bmap; int /*<<< orphan*/  i_state; int /*<<< orphan*/ * i_bh; int /*<<< orphan*/  i_dirty; } ;
struct inode {scalar_t__ i_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  NILFS_I_BMAP ; 
 scalar_t__ NILFS_ROOT_INO ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_bmap_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_btnode_cache_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ nilfs_is_metadata_file_inode (struct inode*) ; 
 int /*<<< orphan*/  nilfs_mdt_clear (struct inode*) ; 
 int /*<<< orphan*/  nilfs_put_root (scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_clear_inode(struct inode *inode)
{
	struct nilfs_inode_info *ii = NILFS_I(inode);

	/*
	 * Free resources allocated in nilfs_read_inode(), here.
	 */
	BUG_ON(!list_empty(&ii->i_dirty));
	brelse(ii->i_bh);
	ii->i_bh = NULL;

	if (nilfs_is_metadata_file_inode(inode))
		nilfs_mdt_clear(inode);

	if (test_bit(NILFS_I_BMAP, &ii->i_state))
		nilfs_bmap_clear(ii->i_bmap);

	nilfs_btnode_cache_clear(&ii->i_btnode_cache);

	if (ii->i_root && inode->i_ino == NILFS_ROOT_INO)
		nilfs_put_root(ii->i_root);
}