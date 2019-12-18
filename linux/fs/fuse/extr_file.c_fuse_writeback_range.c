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
struct inode {int /*<<< orphan*/  i_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int filemap_write_and_wait_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_sync_writes (struct inode*) ; 

__attribute__((used)) static int fuse_writeback_range(struct inode *inode, loff_t start, loff_t end)
{
	int err = filemap_write_and_wait_range(inode->i_mapping, start, end);

	if (!err)
		fuse_sync_writes(inode);

	return err;
}