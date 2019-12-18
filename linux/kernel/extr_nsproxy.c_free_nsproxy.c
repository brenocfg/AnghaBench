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
struct nsproxy {int /*<<< orphan*/  net_ns; int /*<<< orphan*/  cgroup_ns; scalar_t__ pid_ns_for_children; scalar_t__ ipc_ns; scalar_t__ uts_ns; scalar_t__ mnt_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nsproxy*) ; 
 int /*<<< orphan*/  nsproxy_cachep ; 
 int /*<<< orphan*/  put_cgroup_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ipc_ns (scalar_t__) ; 
 int /*<<< orphan*/  put_mnt_ns (scalar_t__) ; 
 int /*<<< orphan*/  put_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pid_ns (scalar_t__) ; 
 int /*<<< orphan*/  put_uts_ns (scalar_t__) ; 

void free_nsproxy(struct nsproxy *ns)
{
	if (ns->mnt_ns)
		put_mnt_ns(ns->mnt_ns);
	if (ns->uts_ns)
		put_uts_ns(ns->uts_ns);
	if (ns->ipc_ns)
		put_ipc_ns(ns->ipc_ns);
	if (ns->pid_ns_for_children)
		put_pid_ns(ns->pid_ns_for_children);
	put_cgroup_ns(ns->cgroup_ns);
	put_net(ns->net_ns);
	kmem_cache_free(nsproxy_cachep, ns);
}