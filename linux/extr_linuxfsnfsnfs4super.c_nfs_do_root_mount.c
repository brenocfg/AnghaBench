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
struct vfsmount {int dummy; } ;
struct file_system_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct vfsmount* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 
 scalar_t__ strchr (char const*,char) ; 
 int strlen (char const*) ; 
 struct vfsmount* vfs_kern_mount (struct file_system_type*,int,char*,void*) ; 

__attribute__((used)) static struct vfsmount *nfs_do_root_mount(struct file_system_type *fs_type,
		int flags, void *data, const char *hostname)
{
	struct vfsmount *root_mnt;
	char *root_devname;
	size_t len;

	len = strlen(hostname) + 5;
	root_devname = kmalloc(len, GFP_KERNEL);
	if (root_devname == NULL)
		return ERR_PTR(-ENOMEM);
	/* Does hostname needs to be enclosed in brackets? */
	if (strchr(hostname, ':'))
		snprintf(root_devname, len, "[%s]:/", hostname);
	else
		snprintf(root_devname, len, "%s:/", hostname);
	root_mnt = vfs_kern_mount(fs_type, flags, root_devname, data);
	kfree(root_devname);
	return root_mnt;
}