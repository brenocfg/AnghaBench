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
typedef  scalar_t__ uid_t ;
struct vfs_ns_cap_data {int /*<<< orphan*/  data; void* magic_etc; void* rootid; } ;
struct vfs_cap_data {void* magic_etc; int /*<<< orphan*/  data; } ;
struct user_namespace {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int __le32 ;
struct TYPE_2__ {struct user_namespace* s_user_ns; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int VFS_CAP_FLAGS_EFFECTIVE ; 
 int VFS_CAP_REVISION_2 ; 
 int VFS_CAP_U32 ; 
 int /*<<< orphan*/  XATTR_NAME_CAPS ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  current_user_ns () ; 
 struct dentry* d_find_any_alias (struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 scalar_t__ from_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_v2header (size_t,struct vfs_cap_data*) ; 
 int /*<<< orphan*/  is_v3header (size_t,struct vfs_cap_data*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (void*) ; 
 int /*<<< orphan*/  make_kuid (struct user_namespace*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rootid_owns_currentns (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ vfs_getxattr_alloc (struct dentry*,int /*<<< orphan*/ ,char**,int,int /*<<< orphan*/ ) ; 

int cap_inode_getsecurity(struct inode *inode, const char *name, void **buffer,
			  bool alloc)
{
	int size, ret;
	kuid_t kroot;
	uid_t root, mappedroot;
	char *tmpbuf = NULL;
	struct vfs_cap_data *cap;
	struct vfs_ns_cap_data *nscap;
	struct dentry *dentry;
	struct user_namespace *fs_ns;

	if (strcmp(name, "capability") != 0)
		return -EOPNOTSUPP;

	dentry = d_find_any_alias(inode);
	if (!dentry)
		return -EINVAL;

	size = sizeof(struct vfs_ns_cap_data);
	ret = (int) vfs_getxattr_alloc(dentry, XATTR_NAME_CAPS,
				 &tmpbuf, size, GFP_NOFS);
	dput(dentry);

	if (ret < 0)
		return ret;

	fs_ns = inode->i_sb->s_user_ns;
	cap = (struct vfs_cap_data *) tmpbuf;
	if (is_v2header((size_t) ret, cap)) {
		/* If this is sizeof(vfs_cap_data) then we're ok with the
		 * on-disk value, so return that.  */
		if (alloc)
			*buffer = tmpbuf;
		else
			kfree(tmpbuf);
		return ret;
	} else if (!is_v3header((size_t) ret, cap)) {
		kfree(tmpbuf);
		return -EINVAL;
	}

	nscap = (struct vfs_ns_cap_data *) tmpbuf;
	root = le32_to_cpu(nscap->rootid);
	kroot = make_kuid(fs_ns, root);

	/* If the root kuid maps to a valid uid in current ns, then return
	 * this as a nscap. */
	mappedroot = from_kuid(current_user_ns(), kroot);
	if (mappedroot != (uid_t)-1 && mappedroot != (uid_t)0) {
		if (alloc) {
			*buffer = tmpbuf;
			nscap->rootid = cpu_to_le32(mappedroot);
		} else
			kfree(tmpbuf);
		return size;
	}

	if (!rootid_owns_currentns(kroot)) {
		kfree(tmpbuf);
		return -EOPNOTSUPP;
	}

	/* This comes from a parent namespace.  Return as a v2 capability */
	size = sizeof(struct vfs_cap_data);
	if (alloc) {
		*buffer = kmalloc(size, GFP_ATOMIC);
		if (*buffer) {
			struct vfs_cap_data *cap = *buffer;
			__le32 nsmagic, magic;
			magic = VFS_CAP_REVISION_2;
			nsmagic = le32_to_cpu(nscap->magic_etc);
			if (nsmagic & VFS_CAP_FLAGS_EFFECTIVE)
				magic |= VFS_CAP_FLAGS_EFFECTIVE;
			memcpy(&cap->data, &nscap->data, sizeof(__le32) * 2 * VFS_CAP_U32);
			cap->magic_etc = cpu_to_le32(magic);
		} else {
			size = -ENOMEM;
		}
	}
	kfree(tmpbuf);
	return size;
}