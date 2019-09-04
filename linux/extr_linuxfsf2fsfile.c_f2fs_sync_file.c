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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  F2FS_I_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_cp_error (int /*<<< orphan*/ ) ; 
 int f2fs_do_sync_file (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int f2fs_sync_file(struct file *file, loff_t start, loff_t end, int datasync)
{
	if (unlikely(f2fs_cp_error(F2FS_I_SB(file_inode(file)))))
		return -EIO;
	return f2fs_do_sync_file(file, start, end, datasync, false);
}