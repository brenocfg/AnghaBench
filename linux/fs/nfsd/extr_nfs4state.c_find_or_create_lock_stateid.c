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
struct nfs4_stid {int dummy; } ;
struct TYPE_2__ {struct nfs4_client* so_client; } ;
struct nfs4_openowner {TYPE_1__ oo_owner; } ;
struct nfs4_ol_stateid {struct nfs4_stid st_stid; int /*<<< orphan*/  st_stateowner; } ;
struct nfs4_lockowner {int dummy; } ;
struct nfs4_file {int dummy; } ;
struct nfs4_client {int /*<<< orphan*/  cl_lock; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct nfs4_ol_stateid* find_lock_stateid (struct nfs4_lockowner*,struct nfs4_file*) ; 
 struct nfs4_ol_stateid* init_lock_stateid (struct nfs4_ol_stateid*,struct nfs4_lockowner*,struct nfs4_file*,struct inode*,struct nfs4_ol_stateid*) ; 
 struct nfs4_stid* nfs4_alloc_stid (struct nfs4_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_free_lock_stateid ; 
 int /*<<< orphan*/  nfs4_put_stid (struct nfs4_stid*) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd4_lock_ol_stateid (struct nfs4_ol_stateid*) ; 
 struct nfs4_ol_stateid* openlockstateid (struct nfs4_stid*) ; 
 struct nfs4_openowner* openowner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stateid_slab ; 

__attribute__((used)) static struct nfs4_ol_stateid *
find_or_create_lock_stateid(struct nfs4_lockowner *lo, struct nfs4_file *fi,
			    struct inode *inode, struct nfs4_ol_stateid *ost,
			    bool *new)
{
	struct nfs4_stid *ns = NULL;
	struct nfs4_ol_stateid *lst;
	struct nfs4_openowner *oo = openowner(ost->st_stateowner);
	struct nfs4_client *clp = oo->oo_owner.so_client;

	*new = false;
	spin_lock(&clp->cl_lock);
	lst = find_lock_stateid(lo, fi);
	spin_unlock(&clp->cl_lock);
	if (lst != NULL) {
		if (nfsd4_lock_ol_stateid(lst) == nfs_ok)
			goto out;
		nfs4_put_stid(&lst->st_stid);
	}
	ns = nfs4_alloc_stid(clp, stateid_slab, nfs4_free_lock_stateid);
	if (ns == NULL)
		return NULL;

	lst = init_lock_stateid(openlockstateid(ns), lo, fi, inode, ost);
	if (lst == openlockstateid(ns))
		*new = true;
	else
		nfs4_put_stid(ns);
out:
	return lst;
}