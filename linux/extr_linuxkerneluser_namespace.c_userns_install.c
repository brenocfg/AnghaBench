#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct user_namespace {int dummy; } ;
struct nsproxy {int dummy; } ;
struct ns_common {int dummy; } ;
struct cred {int /*<<< orphan*/  user_ns; } ;
struct TYPE_5__ {TYPE_1__* fs; } ;
struct TYPE_4__ {int users; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int commit_creds (struct cred*) ; 
 TYPE_2__* current ; 
 struct user_namespace* current_user_ns () ; 
 int /*<<< orphan*/  get_user_ns (struct user_namespace*) ; 
 int /*<<< orphan*/  ns_capable (struct user_namespace*,int /*<<< orphan*/ ) ; 
 struct cred* prepare_creds () ; 
 int /*<<< orphan*/  put_user_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cred_user_ns (struct cred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_group_empty (TYPE_2__*) ; 
 struct user_namespace* to_user_ns (struct ns_common*) ; 

__attribute__((used)) static int userns_install(struct nsproxy *nsproxy, struct ns_common *ns)
{
	struct user_namespace *user_ns = to_user_ns(ns);
	struct cred *cred;

	/* Don't allow gaining capabilities by reentering
	 * the same user namespace.
	 */
	if (user_ns == current_user_ns())
		return -EINVAL;

	/* Tasks that share a thread group must share a user namespace */
	if (!thread_group_empty(current))
		return -EINVAL;

	if (current->fs->users != 1)
		return -EINVAL;

	if (!ns_capable(user_ns, CAP_SYS_ADMIN))
		return -EPERM;

	cred = prepare_creds();
	if (!cred)
		return -ENOMEM;

	put_user_ns(cred->user_ns);
	set_cred_user_ns(cred, get_user_ns(user_ns));

	return commit_creds(cred);
}