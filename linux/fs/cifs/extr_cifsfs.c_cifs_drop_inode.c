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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct cifs_sb_info {int mnt_cifs_flags; } ;

/* Variables and functions */
 int CIFS_MOUNT_SERVER_INUM ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ generic_drop_inode (struct inode*) ; 

__attribute__((used)) static int cifs_drop_inode(struct inode *inode)
{
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);

	/* no serverino => unconditional eviction */
	return !(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SERVER_INUM) ||
		generic_drop_inode(inode);
}