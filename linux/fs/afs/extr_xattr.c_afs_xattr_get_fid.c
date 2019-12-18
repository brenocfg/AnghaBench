#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xattr_handler {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int vid; int vnode_hi; int vnode; int unique; } ;
struct afs_vnode {TYPE_1__ fid; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (struct inode*) ; 
 int ERANGE ; 
 int /*<<< orphan*/  memcpy (void*,char*,size_t) ; 
 size_t sprintf (char*,char*,int,...) ; 

__attribute__((used)) static int afs_xattr_get_fid(const struct xattr_handler *handler,
			     struct dentry *dentry,
			     struct inode *inode, const char *name,
			     void *buffer, size_t size)
{
	struct afs_vnode *vnode = AFS_FS_I(inode);
	char text[16 + 1 + 24 + 1 + 8 + 1];
	size_t len;

	/* The volume ID is 64-bit, the vnode ID is 96-bit and the
	 * uniquifier is 32-bit.
	 */
	len = sprintf(text, "%llx:", vnode->fid.vid);
	if (vnode->fid.vnode_hi)
		len += sprintf(text + len, "%x%016llx",
			       vnode->fid.vnode_hi, vnode->fid.vnode);
	else
		len += sprintf(text + len, "%llx", vnode->fid.vnode);
	len += sprintf(text + len, ":%x", vnode->fid.unique);

	if (size == 0)
		return len;
	if (len > size)
		return -ERANGE;
	memcpy(buffer, text, len);
	return len;
}