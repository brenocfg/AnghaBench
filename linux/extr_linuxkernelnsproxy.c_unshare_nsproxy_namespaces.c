#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct user_namespace {int dummy; } ;
struct nsproxy {int dummy; } ;
struct fs_struct {int dummy; } ;
struct cred {struct user_namespace* user_ns; } ;
struct TYPE_3__ {struct fs_struct* fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 unsigned long CLONE_NEWCGROUP ; 
 unsigned long CLONE_NEWIPC ; 
 unsigned long CLONE_NEWNET ; 
 unsigned long CLONE_NEWNS ; 
 unsigned long CLONE_NEWPID ; 
 unsigned long CLONE_NEWUTS ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct nsproxy*) ; 
 int PTR_ERR (struct nsproxy*) ; 
 struct nsproxy* create_new_namespaces (unsigned long,TYPE_1__*,struct user_namespace*,struct fs_struct*) ; 
 TYPE_1__* current ; 
 struct user_namespace* current_user_ns () ; 
 int /*<<< orphan*/  ns_capable (struct user_namespace*,int /*<<< orphan*/ ) ; 

int unshare_nsproxy_namespaces(unsigned long unshare_flags,
	struct nsproxy **new_nsp, struct cred *new_cred, struct fs_struct *new_fs)
{
	struct user_namespace *user_ns;
	int err = 0;

	if (!(unshare_flags & (CLONE_NEWNS | CLONE_NEWUTS | CLONE_NEWIPC |
			       CLONE_NEWNET | CLONE_NEWPID | CLONE_NEWCGROUP)))
		return 0;

	user_ns = new_cred ? new_cred->user_ns : current_user_ns();
	if (!ns_capable(user_ns, CAP_SYS_ADMIN))
		return -EPERM;

	*new_nsp = create_new_namespaces(unshare_flags, current, user_ns,
					 new_fs ? new_fs : current->fs);
	if (IS_ERR(*new_nsp)) {
		err = PTR_ERR(*new_nsp);
		goto out;
	}

out:
	return err;
}