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
typedef  scalar_t__ u64 ;
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_3__ {scalar_t__ nfs; } ;
struct TYPE_4__ {TYPE_1__ options; } ;

/* Variables and functions */
 scalar_t__ FAT_NFS_NOSTALE_RO ; 
 scalar_t__ MSDOS_FSINFO_INO ; 
 scalar_t__ MSDOS_ROOT_INO ; 
 TYPE_2__* MSDOS_SB (struct super_block*) ; 
 struct inode* fat_iget (struct super_block*,int /*<<< orphan*/ ) ; 
 struct inode* ilookup (struct super_block*,scalar_t__) ; 

__attribute__((used)) static struct inode *fat_ilookup(struct super_block *sb, u64 ino, loff_t i_pos)
{
	if (MSDOS_SB(sb)->options.nfs == FAT_NFS_NOSTALE_RO)
		return fat_iget(sb, i_pos);

	else {
		if ((ino < MSDOS_ROOT_INO) || (ino == MSDOS_FSINFO_INO))
			return NULL;
		return ilookup(sb, ino);
	}
}