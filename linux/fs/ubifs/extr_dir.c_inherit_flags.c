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
typedef  int /*<<< orphan*/  umode_t ;
struct ubifs_inode {int flags; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int UBIFS_COMPR_FL ; 
 int UBIFS_DIRSYNC_FL ; 
 int UBIFS_SYNC_FL ; 
 struct ubifs_inode* ubifs_inode (struct inode const*) ; 

__attribute__((used)) static int inherit_flags(const struct inode *dir, umode_t mode)
{
	int flags;
	const struct ubifs_inode *ui = ubifs_inode(dir);

	if (!S_ISDIR(dir->i_mode))
		/*
		 * The parent is not a directory, which means that an extended
		 * attribute inode is being created. No flags.
		 */
		return 0;

	flags = ui->flags & (UBIFS_COMPR_FL | UBIFS_SYNC_FL | UBIFS_DIRSYNC_FL);
	if (!S_ISDIR(mode))
		/* The "DIRSYNC" flag only applies to directories */
		flags &= ~UBIFS_DIRSYNC_FL;
	return flags;
}