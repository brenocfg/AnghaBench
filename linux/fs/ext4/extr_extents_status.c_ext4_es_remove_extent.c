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
struct inode {int /*<<< orphan*/  i_ino; } ;
typedef  scalar_t__ ext4_lblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_es_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int __es_remove_extent (struct inode*,scalar_t__,scalar_t__,int*) ; 
 int /*<<< orphan*/  es_debug (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_da_release_space (struct inode*,int) ; 
 int /*<<< orphan*/  ext4_es_print_tree (struct inode*) ; 
 int /*<<< orphan*/  trace_ext4_es_remove_extent (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int ext4_es_remove_extent(struct inode *inode, ext4_lblk_t lblk,
			  ext4_lblk_t len)
{
	ext4_lblk_t end;
	int err = 0;
	int reserved = 0;

	trace_ext4_es_remove_extent(inode, lblk, len);
	es_debug("remove [%u/%u) from extent status tree of inode %lu\n",
		 lblk, len, inode->i_ino);

	if (!len)
		return err;

	end = lblk + len - 1;
	BUG_ON(end < lblk);

	/*
	 * ext4_clear_inode() depends on us taking i_es_lock unconditionally
	 * so that we are sure __es_shrink() is done with the inode before it
	 * is reclaimed.
	 */
	write_lock(&EXT4_I(inode)->i_es_lock);
	err = __es_remove_extent(inode, lblk, end, &reserved);
	write_unlock(&EXT4_I(inode)->i_es_lock);
	ext4_es_print_tree(inode);
	ext4_da_release_space(inode, reserved);
	return err;
}