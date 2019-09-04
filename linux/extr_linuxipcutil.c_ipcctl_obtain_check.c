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
struct kern_ipc_perm {int /*<<< orphan*/  uid; int /*<<< orphan*/  cuid; } ;
struct ipc_namespace {int /*<<< orphan*/  user_ns; } ;
struct ipc_ids {int dummy; } ;
struct ipc64_perm {int /*<<< orphan*/  mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EPERM ; 
 struct kern_ipc_perm* ERR_PTR (int) ; 
 int IPC_SET ; 
 scalar_t__ IS_ERR (struct kern_ipc_perm*) ; 
 int PTR_ERR (struct kern_ipc_perm*) ; 
 int /*<<< orphan*/  audit_ipc_obj (struct kern_ipc_perm*) ; 
 int /*<<< orphan*/  audit_ipc_set_perm (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_euid () ; 
 struct kern_ipc_perm* ipc_obtain_object_check (struct ipc_ids*,int) ; 
 scalar_t__ ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct kern_ipc_perm *ipcctl_obtain_check(struct ipc_namespace *ns,
					struct ipc_ids *ids, int id, int cmd,
					struct ipc64_perm *perm, int extra_perm)
{
	kuid_t euid;
	int err = -EPERM;
	struct kern_ipc_perm *ipcp;

	ipcp = ipc_obtain_object_check(ids, id);
	if (IS_ERR(ipcp)) {
		err = PTR_ERR(ipcp);
		goto err;
	}

	audit_ipc_obj(ipcp);
	if (cmd == IPC_SET)
		audit_ipc_set_perm(extra_perm, perm->uid,
				   perm->gid, perm->mode);

	euid = current_euid();
	if (uid_eq(euid, ipcp->cuid) || uid_eq(euid, ipcp->uid)  ||
	    ns_capable(ns->user_ns, CAP_SYS_ADMIN))
		return ipcp; /* successful lookup */
err:
	return ERR_PTR(err);
}