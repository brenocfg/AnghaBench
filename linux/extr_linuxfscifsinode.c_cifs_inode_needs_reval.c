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
struct inode {int i_nlink; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct cifs_sb_info {scalar_t__ actimeo; int mnt_cifs_flags; } ;
struct cifsInodeInfo {scalar_t__ time; } ;

/* Variables and functions */
 scalar_t__ CIFS_CACHE_READ (struct cifsInodeInfo*) ; 
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 int CIFS_MOUNT_SERVER_INUM ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  lookupCacheEnabled ; 
 int /*<<< orphan*/  time_in_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
cifs_inode_needs_reval(struct inode *inode)
{
	struct cifsInodeInfo *cifs_i = CIFS_I(inode);
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);

	if (cifs_i->time == 0)
		return true;

	if (CIFS_CACHE_READ(cifs_i))
		return false;

	if (!lookupCacheEnabled)
		return true;

	if (!cifs_sb->actimeo)
		return true;

	if (!time_in_range(jiffies, cifs_i->time,
				cifs_i->time + cifs_sb->actimeo))
		return true;

	/* hardlinked files w/ noserverino get "special" treatment */
	if (!(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SERVER_INUM) &&
	    S_ISREG(inode->i_mode) && inode->i_nlink != 1)
		return true;

	return false;
}