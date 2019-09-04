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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_io_info {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_ATOMIC_WRITTEN_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LFS ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_is_atomic_file (struct inode*) ; 
 scalar_t__ is_cold_data (int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

bool f2fs_should_update_outplace(struct inode *inode, struct f2fs_io_info *fio)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);

	if (test_opt(sbi, LFS))
		return true;
	if (S_ISDIR(inode->i_mode))
		return true;
	if (f2fs_is_atomic_file(inode))
		return true;
	if (fio) {
		if (is_cold_data(fio->page))
			return true;
		if (IS_ATOMIC_WRITTEN_PAGE(fio->page))
			return true;
	}
	return false;
}