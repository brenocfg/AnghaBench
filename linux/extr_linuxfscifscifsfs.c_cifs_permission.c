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
 int CIFS_MOUNT_NO_PERM ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int MAY_EXEC ; 
 int /*<<< orphan*/  execute_ok (struct inode*) ; 
 int generic_permission (struct inode*,int) ; 

__attribute__((used)) static int cifs_permission(struct inode *inode, int mask)
{
	struct cifs_sb_info *cifs_sb;

	cifs_sb = CIFS_SB(inode->i_sb);

	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_PERM) {
		if ((mask & MAY_EXEC) && !execute_ok(inode))
			return -EACCES;
		else
			return 0;
	} else /* file mode might have been restricted at mount time
		on the client (above and beyond ACL on servers) for
		servers which do not support setting and viewing mode bits,
		so allowing client to check permissions is useful */
		return generic_permission(inode, mask);
}