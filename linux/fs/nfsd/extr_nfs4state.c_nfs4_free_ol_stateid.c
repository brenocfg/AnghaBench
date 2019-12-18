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
struct nfs4_stid {int dummy; } ;
struct nfs4_ol_stateid {scalar_t__ st_stateowner; int /*<<< orphan*/  st_clnt_odstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nfs4_stid*) ; 
 int /*<<< orphan*/  nfs4_put_stateowner (scalar_t__) ; 
 struct nfs4_ol_stateid* openlockstateid (struct nfs4_stid*) ; 
 int /*<<< orphan*/  put_clnt_odstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_all_access (struct nfs4_ol_stateid*) ; 
 int /*<<< orphan*/  stateid_slab ; 

__attribute__((used)) static void nfs4_free_ol_stateid(struct nfs4_stid *stid)
{
	struct nfs4_ol_stateid *stp = openlockstateid(stid);

	put_clnt_odstate(stp->st_clnt_odstate);
	release_all_access(stp);
	if (stp->st_stateowner)
		nfs4_put_stateowner(stp->st_stateowner);
	kmem_cache_free(stateid_slab, stid);
}