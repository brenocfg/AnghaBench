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
struct rpc_cred {int dummy; } ;
struct nfs4_ff_layout_mirror {int /*<<< orphan*/  mirror_ds; int /*<<< orphan*/  rw_cred; int /*<<< orphan*/  ro_cred; struct nfs4_ff_layout_mirror* fh_versions; } ;

/* Variables and functions */
 int /*<<< orphan*/  ff_layout_remove_mirror (struct nfs4_ff_layout_mirror*) ; 
 int /*<<< orphan*/  kfree (struct nfs4_ff_layout_mirror*) ; 
 int /*<<< orphan*/  nfs4_ff_layout_put_deviceid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_rpccred (struct rpc_cred*) ; 
 struct rpc_cred* rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ff_layout_free_mirror(struct nfs4_ff_layout_mirror *mirror)
{
	struct rpc_cred	*cred;

	ff_layout_remove_mirror(mirror);
	kfree(mirror->fh_versions);
	cred = rcu_access_pointer(mirror->ro_cred);
	if (cred)
		put_rpccred(cred);
	cred = rcu_access_pointer(mirror->rw_cred);
	if (cred)
		put_rpccred(cred);
	nfs4_ff_layout_put_deviceid(mirror->mirror_ds);
	kfree(mirror);
}