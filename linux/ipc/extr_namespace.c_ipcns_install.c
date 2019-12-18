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
struct nsproxy {int /*<<< orphan*/  ipc_ns; } ;
struct ns_common {int dummy; } ;
struct ipc_namespace {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EPERM ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  exit_sem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ipc_ns (struct ipc_namespace*) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ipc_ns (int /*<<< orphan*/ ) ; 
 struct ipc_namespace* to_ipc_ns (struct ns_common*) ; 

__attribute__((used)) static int ipcns_install(struct nsproxy *nsproxy, struct ns_common *new)
{
	struct ipc_namespace *ns = to_ipc_ns(new);
	if (!ns_capable(ns->user_ns, CAP_SYS_ADMIN) ||
	    !ns_capable(current_user_ns(), CAP_SYS_ADMIN))
		return -EPERM;

	/* Ditch state from the old ipc namespace */
	exit_sem(current);
	put_ipc_ns(nsproxy->ipc_ns);
	nsproxy->ipc_ns = get_ipc_ns(ns);
	return 0;
}