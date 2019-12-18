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
struct super_block {int dummy; } ;
struct inode {int i_nlink; struct super_block* i_sb; } ;
struct TYPE_4__ {scalar_t__ i_start; } ;
struct TYPE_3__ {scalar_t__ root_cluster; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_2__* MSDOS_I (struct inode*) ; 
 TYPE_1__* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  fat_fs_error (struct super_block*,char*) ; 

__attribute__((used)) static int fat_validate_dir(struct inode *dir)
{
	struct super_block *sb = dir->i_sb;

	if (dir->i_nlink < 2) {
		/* Directory should have "."/".." entries at least. */
		fat_fs_error(sb, "corrupted directory (invalid entries)");
		return -EIO;
	}
	if (MSDOS_I(dir)->i_start == 0 ||
	    MSDOS_I(dir)->i_start == MSDOS_SB(sb)->root_cluster) {
		/* Directory should point valid cluster. */
		fat_fs_error(sb, "corrupted directory (invalid i_start)");
		return -EIO;
	}
	return 0;
}