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
struct afs_vnode {TYPE_1__* volume; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (struct inode*) ; 
 int ERANGE ; 
 int /*<<< orphan*/  memcpy (void*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int afs_xattr_get_volume(const struct xattr_handler *handler,
			      struct dentry *dentry,
			      struct inode *inode, const char *name,
			      void *buffer, size_t size)
{
	struct afs_vnode *vnode = AFS_FS_I(inode);
	const char *volname = vnode->volume->name;
	size_t namelen;

	namelen = strlen(volname);
	if (size == 0)
		return namelen;
	if (namelen > size)
		return -ERANGE;
	memcpy(buffer, volname, namelen);
	return namelen;
}