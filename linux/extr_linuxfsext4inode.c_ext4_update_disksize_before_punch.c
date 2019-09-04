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
struct inode {int dummy; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {scalar_t__ i_disksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_HT_MISC ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_update_i_disksize (struct inode*,scalar_t__) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_is_locked (struct inode*) ; 

int ext4_update_disksize_before_punch(struct inode *inode, loff_t offset,
				      loff_t len)
{
	handle_t *handle;
	loff_t size = i_size_read(inode);

	WARN_ON(!inode_is_locked(inode));
	if (offset > size || offset + len < size)
		return 0;

	if (EXT4_I(inode)->i_disksize >= size)
		return 0;

	handle = ext4_journal_start(inode, EXT4_HT_MISC, 1);
	if (IS_ERR(handle))
		return PTR_ERR(handle);
	ext4_update_i_disksize(inode, size);
	ext4_mark_inode_dirty(handle, inode);
	ext4_journal_stop(handle);

	return 0;
}