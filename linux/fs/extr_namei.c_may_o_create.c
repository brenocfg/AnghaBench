#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct user_namespace {int dummy; } ;
struct path {TYPE_2__* dentry; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_inode; TYPE_1__* d_sb; } ;
struct TYPE_3__ {struct user_namespace* s_user_ns; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 int MAY_EXEC ; 
 int MAY_WRITE ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int inode_permission (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kgid_has_mapping (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuid_has_mapping (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int security_inode_create (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 int security_path_mknod (struct path const*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int may_o_create(const struct path *dir, struct dentry *dentry, umode_t mode)
{
	struct user_namespace *s_user_ns;
	int error = security_path_mknod(dir, dentry, mode, 0);
	if (error)
		return error;

	s_user_ns = dir->dentry->d_sb->s_user_ns;
	if (!kuid_has_mapping(s_user_ns, current_fsuid()) ||
	    !kgid_has_mapping(s_user_ns, current_fsgid()))
		return -EOVERFLOW;

	error = inode_permission(dir->dentry->d_inode, MAY_WRITE | MAY_EXEC);
	if (error)
		return error;

	return security_inode_create(dir->dentry->d_inode, dentry, mode);
}