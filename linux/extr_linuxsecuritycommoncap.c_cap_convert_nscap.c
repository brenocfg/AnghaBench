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
typedef  int uid_t ;
struct vfs_ns_cap_data {int /*<<< orphan*/  data; void* magic_etc; void* rootid; } ;
struct vfs_cap_data {int /*<<< orphan*/  data; int /*<<< orphan*/  magic_etc; } ;
struct user_namespace {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {struct user_namespace* s_user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SETFCAP ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int VFS_CAP_FLAGS_EFFECTIVE ; 
 int VFS_CAP_REVISION_3 ; 
 int VFS_CAP_U32 ; 
 size_t XATTR_CAPS_SZ_2 ; 
 int /*<<< orphan*/  capable_wrt_inode_uidgid (struct inode*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 struct user_namespace* current_user_ns () ; 
 struct inode* d_backing_inode (struct dentry*) ; 
 int from_kuid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 struct vfs_ns_cap_data* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ns_capable (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rootid_from_xattr (void*,size_t,struct user_namespace*) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validheader (size_t,struct vfs_cap_data const*) ; 

int cap_convert_nscap(struct dentry *dentry, void **ivalue, size_t size)
{
	struct vfs_ns_cap_data *nscap;
	uid_t nsrootid;
	const struct vfs_cap_data *cap = *ivalue;
	__u32 magic, nsmagic;
	struct inode *inode = d_backing_inode(dentry);
	struct user_namespace *task_ns = current_user_ns(),
		*fs_ns = inode->i_sb->s_user_ns;
	kuid_t rootid;
	size_t newsize;

	if (!*ivalue)
		return -EINVAL;
	if (!validheader(size, cap))
		return -EINVAL;
	if (!capable_wrt_inode_uidgid(inode, CAP_SETFCAP))
		return -EPERM;
	if (size == XATTR_CAPS_SZ_2)
		if (ns_capable(inode->i_sb->s_user_ns, CAP_SETFCAP))
			/* user is privileged, just write the v2 */
			return size;

	rootid = rootid_from_xattr(*ivalue, size, task_ns);
	if (!uid_valid(rootid))
		return -EINVAL;

	nsrootid = from_kuid(fs_ns, rootid);
	if (nsrootid == -1)
		return -EINVAL;

	newsize = sizeof(struct vfs_ns_cap_data);
	nscap = kmalloc(newsize, GFP_ATOMIC);
	if (!nscap)
		return -ENOMEM;
	nscap->rootid = cpu_to_le32(nsrootid);
	nsmagic = VFS_CAP_REVISION_3;
	magic = le32_to_cpu(cap->magic_etc);
	if (magic & VFS_CAP_FLAGS_EFFECTIVE)
		nsmagic |= VFS_CAP_FLAGS_EFFECTIVE;
	nscap->magic_etc = cpu_to_le32(nsmagic);
	memcpy(&nscap->data, &cap->data, sizeof(__le32) * 2 * VFS_CAP_U32);

	kvfree(*ivalue);
	*ivalue = nscap;
	return newsize;
}