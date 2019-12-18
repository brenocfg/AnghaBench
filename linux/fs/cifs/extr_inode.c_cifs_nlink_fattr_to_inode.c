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
struct inode {int i_state; } ;
struct cifs_fattr {int cf_flags; int cf_cifsattrs; int cf_nlink; } ;

/* Variables and functions */
 int ATTR_DIRECTORY ; 
 int CIFS_FATTR_UNKNOWN_NLINK ; 
 int I_NEW ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 

__attribute__((used)) static void
cifs_nlink_fattr_to_inode(struct inode *inode, struct cifs_fattr *fattr)
{
	/*
	 * if we're in a situation where we can't trust what we
	 * got from the server (readdir, some non-unix cases)
	 * fake reasonable values
	 */
	if (fattr->cf_flags & CIFS_FATTR_UNKNOWN_NLINK) {
		/* only provide fake values on a new inode */
		if (inode->i_state & I_NEW) {
			if (fattr->cf_cifsattrs & ATTR_DIRECTORY)
				set_nlink(inode, 2);
			else
				set_nlink(inode, 1);
		}
		return;
	}

	/* we trust the server, so update it */
	set_nlink(inode, fattr->cf_nlink);
}