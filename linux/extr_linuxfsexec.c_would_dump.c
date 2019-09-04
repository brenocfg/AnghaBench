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
struct user_namespace {struct user_namespace* parent; } ;
struct linux_binprm {TYPE_1__* mm; int /*<<< orphan*/  interp_flags; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct user_namespace* user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINPRM_FLAGS_ENFORCE_NONDUMP ; 
 int /*<<< orphan*/  MAY_READ ; 
 struct inode* file_inode (struct file*) ; 
 struct user_namespace* get_user_ns (struct user_namespace*) ; 
 struct user_namespace init_user_ns ; 
 scalar_t__ inode_permission (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  privileged_wrt_inode_uidgid (struct user_namespace*,struct inode*) ; 
 int /*<<< orphan*/  put_user_ns (struct user_namespace*) ; 

void would_dump(struct linux_binprm *bprm, struct file *file)
{
	struct inode *inode = file_inode(file);
	if (inode_permission(inode, MAY_READ) < 0) {
		struct user_namespace *old, *user_ns;
		bprm->interp_flags |= BINPRM_FLAGS_ENFORCE_NONDUMP;

		/* Ensure mm->user_ns contains the executable */
		user_ns = old = bprm->mm->user_ns;
		while ((user_ns != &init_user_ns) &&
		       !privileged_wrt_inode_uidgid(user_ns, inode))
			user_ns = user_ns->parent;

		if (old != user_ns) {
			bprm->mm->user_ns = get_user_ns(user_ns);
			put_user_ns(old);
		}
	}
}