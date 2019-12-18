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
struct cifsInodeInfo {unsigned int oplock; int /*<<< orphan*/  vfs_inode; } ;
typedef  int /*<<< orphan*/  message ;
typedef  int __u32 ;

/* Variables and functions */
 unsigned int CIFS_CACHE_HANDLE_FLG ; 
 unsigned int CIFS_CACHE_READ_FLG ; 
 unsigned int CIFS_CACHE_WRITE_FLG ; 
 int /*<<< orphan*/  FYI ; 
 int SMB2_LEASE_HANDLE_CACHING_HE ; 
 int SMB2_LEASE_READ_CACHING_HE ; 
 int SMB2_LEASE_WRITE_CACHING_HE ; 
 int SMB2_OPLOCK_LEVEL_EXCLUSIVE ; 
 int SMB2_OPLOCK_LEVEL_NOCHANGE ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 void smb2_set_oplock_level (struct cifsInodeInfo*,int,unsigned int,int*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void
smb21_set_oplock_level(struct cifsInodeInfo *cinode, __u32 oplock,
		       unsigned int epoch, bool *purge_cache)
{
	char message[5] = {0};
	unsigned int new_oplock = 0;

	oplock &= 0xFF;
	if (oplock == SMB2_OPLOCK_LEVEL_NOCHANGE)
		return;

	/* Check if the server granted an oplock rather than a lease */
	if (oplock & SMB2_OPLOCK_LEVEL_EXCLUSIVE)
		return smb2_set_oplock_level(cinode, oplock, epoch,
					     purge_cache);

	if (oplock & SMB2_LEASE_READ_CACHING_HE) {
		new_oplock |= CIFS_CACHE_READ_FLG;
		strcat(message, "R");
	}
	if (oplock & SMB2_LEASE_HANDLE_CACHING_HE) {
		new_oplock |= CIFS_CACHE_HANDLE_FLG;
		strcat(message, "H");
	}
	if (oplock & SMB2_LEASE_WRITE_CACHING_HE) {
		new_oplock |= CIFS_CACHE_WRITE_FLG;
		strcat(message, "W");
	}
	if (!new_oplock)
		strncpy(message, "None", sizeof(message));

	cinode->oplock = new_oplock;
	cifs_dbg(FYI, "%s Lease granted on inode %p\n", message,
		 &cinode->vfs_inode);
}