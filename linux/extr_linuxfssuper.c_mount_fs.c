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
struct super_block {scalar_t__ s_maxbytes; int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_bdi; } ;
struct file_system_type {int fs_flags; int /*<<< orphan*/  name; struct dentry* (* mount ) (struct file_system_type*,int,char const*,void*) ;} ;
struct dentry {struct super_block* d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 struct dentry* ERR_PTR (int) ; 
 int FS_BINARY_MOUNTDATA ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  SB_BORN ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 char* alloc_secdata () ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  free_secdata (char*) ; 
 int security_sb_copy_data (void*,char*) ; 
 int security_sb_kern_mount (struct super_block*,int,char*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 struct dentry* stub1 (struct file_system_type*,int,char const*,void*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

struct dentry *
mount_fs(struct file_system_type *type, int flags, const char *name, void *data)
{
	struct dentry *root;
	struct super_block *sb;
	char *secdata = NULL;
	int error = -ENOMEM;

	if (data && !(type->fs_flags & FS_BINARY_MOUNTDATA)) {
		secdata = alloc_secdata();
		if (!secdata)
			goto out;

		error = security_sb_copy_data(data, secdata);
		if (error)
			goto out_free_secdata;
	}

	root = type->mount(type, flags, name, data);
	if (IS_ERR(root)) {
		error = PTR_ERR(root);
		goto out_free_secdata;
	}
	sb = root->d_sb;
	BUG_ON(!sb);
	WARN_ON(!sb->s_bdi);

	/*
	 * Write barrier is for super_cache_count(). We place it before setting
	 * SB_BORN as the data dependency between the two functions is the
	 * superblock structure contents that we just set up, not the SB_BORN
	 * flag.
	 */
	smp_wmb();
	sb->s_flags |= SB_BORN;

	error = security_sb_kern_mount(sb, flags, secdata);
	if (error)
		goto out_sb;

	/*
	 * filesystems should never set s_maxbytes larger than MAX_LFS_FILESIZE
	 * but s_maxbytes was an unsigned long long for many releases. Throw
	 * this warning for a little while to try and catch filesystems that
	 * violate this rule.
	 */
	WARN((sb->s_maxbytes < 0), "%s set sb->s_maxbytes to "
		"negative value (%lld)\n", type->name, sb->s_maxbytes);

	up_write(&sb->s_umount);
	free_secdata(secdata);
	return root;
out_sb:
	dput(root);
	deactivate_locked_super(sb);
out_free_secdata:
	free_secdata(secdata);
out:
	return ERR_PTR(error);
}