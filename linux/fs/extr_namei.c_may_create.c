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
struct user_namespace {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct dentry {scalar_t__ d_inode; } ;
struct TYPE_2__ {struct user_namespace* s_user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_TYPE_CHILD_CREATE ; 
 int EEXIST ; 
 int ENOENT ; 
 int EOVERFLOW ; 
 scalar_t__ IS_DEADDIR (struct inode*) ; 
 int MAY_EXEC ; 
 int MAY_WRITE ; 
 int /*<<< orphan*/  audit_inode_child (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int inode_permission (struct inode*,int) ; 
 int /*<<< orphan*/  kgid_has_mapping (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuid_has_mapping (struct user_namespace*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int may_create(struct inode *dir, struct dentry *child)
{
	struct user_namespace *s_user_ns;
	audit_inode_child(dir, child, AUDIT_TYPE_CHILD_CREATE);
	if (child->d_inode)
		return -EEXIST;
	if (IS_DEADDIR(dir))
		return -ENOENT;
	s_user_ns = dir->i_sb->s_user_ns;
	if (!kuid_has_mapping(s_user_ns, current_fsuid()) ||
	    !kgid_has_mapping(s_user_ns, current_fsgid()))
		return -EOVERFLOW;
	return inode_permission(dir, MAY_WRITE | MAY_EXEC);
}