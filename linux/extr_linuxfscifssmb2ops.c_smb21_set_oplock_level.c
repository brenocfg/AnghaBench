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
struct cifsInodeInfo {int /*<<< orphan*/  vfs_inode; int /*<<< orphan*/  oplock; } ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_CACHE_HANDLE_FLG ; 
 int /*<<< orphan*/  CIFS_CACHE_READ_FLG ; 
 int /*<<< orphan*/  CIFS_CACHE_WRITE_FLG ; 
 int /*<<< orphan*/  FYI ; 
 int SMB2_LEASE_HANDLE_CACHING_HE ; 
 int SMB2_LEASE_READ_CACHING_HE ; 
 int SMB2_LEASE_WRITE_CACHING_HE ; 
 int SMB2_OPLOCK_LEVEL_NOCHANGE ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static void
smb21_set_oplock_level(struct cifsInodeInfo *cinode, __u32 oplock,
		       unsigned int epoch, bool *purge_cache)
{
	char message[5] = {0};

	oplock &= 0xFF;
	if (oplock == SMB2_OPLOCK_LEVEL_NOCHANGE)
		return;

	cinode->oplock = 0;
	if (oplock & SMB2_LEASE_READ_CACHING_HE) {
		cinode->oplock |= CIFS_CACHE_READ_FLG;
		strcat(message, "R");
	}
	if (oplock & SMB2_LEASE_HANDLE_CACHING_HE) {
		cinode->oplock |= CIFS_CACHE_HANDLE_FLG;
		strcat(message, "H");
	}
	if (oplock & SMB2_LEASE_WRITE_CACHING_HE) {
		cinode->oplock |= CIFS_CACHE_WRITE_FLG;
		strcat(message, "W");
	}
	if (!cinode->oplock)
		strcat(message, "None");
	cifs_dbg(FYI, "%s Lease granted on inode %p\n", message,
		 &cinode->vfs_inode);
}