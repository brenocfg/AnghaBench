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
struct cifsInodeInfo {scalar_t__ oplock; int /*<<< orphan*/  vfs_inode; } ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ CIFS_CACHE_READ_FLG ; 
 scalar_t__ CIFS_CACHE_RHW_FLG ; 
 scalar_t__ CIFS_CACHE_RW_FLG ; 
 int /*<<< orphan*/  FYI ; 
 int SMB2_OPLOCK_LEVEL_BATCH ; 
 int SMB2_OPLOCK_LEVEL_EXCLUSIVE ; 
 int SMB2_OPLOCK_LEVEL_II ; 
 int SMB2_OPLOCK_LEVEL_NOCHANGE ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
smb2_set_oplock_level(struct cifsInodeInfo *cinode, __u32 oplock,
		      unsigned int epoch, bool *purge_cache)
{
	oplock &= 0xFF;
	if (oplock == SMB2_OPLOCK_LEVEL_NOCHANGE)
		return;
	if (oplock == SMB2_OPLOCK_LEVEL_BATCH) {
		cinode->oplock = CIFS_CACHE_RHW_FLG;
		cifs_dbg(FYI, "Batch Oplock granted on inode %p\n",
			 &cinode->vfs_inode);
	} else if (oplock == SMB2_OPLOCK_LEVEL_EXCLUSIVE) {
		cinode->oplock = CIFS_CACHE_RW_FLG;
		cifs_dbg(FYI, "Exclusive Oplock granted on inode %p\n",
			 &cinode->vfs_inode);
	} else if (oplock == SMB2_OPLOCK_LEVEL_II) {
		cinode->oplock = CIFS_CACHE_READ_FLG;
		cifs_dbg(FYI, "Level II Oplock granted on inode %p\n",
			 &cinode->vfs_inode);
	} else
		cinode->oplock = 0;
}