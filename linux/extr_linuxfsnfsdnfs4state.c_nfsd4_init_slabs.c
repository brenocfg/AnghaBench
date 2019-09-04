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
struct nfs4_openowner {int dummy; } ;
struct nfs4_ol_stateid {int dummy; } ;
struct nfs4_lockowner {int dummy; } ;
struct nfs4_file {int dummy; } ;
struct nfs4_delegation {int dummy; } ;
struct nfs4_clnt_odstate {int dummy; } ;
struct nfs4_client {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * client_slab ; 
 int /*<<< orphan*/ * deleg_slab ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/ * file_slab ; 
 void* kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lockowner_slab ; 
 int /*<<< orphan*/ * odstate_slab ; 
 int /*<<< orphan*/ * openowner_slab ; 
 int /*<<< orphan*/ * stateid_slab ; 

int
nfsd4_init_slabs(void)
{
	client_slab = kmem_cache_create("nfsd4_clients",
			sizeof(struct nfs4_client), 0, 0, NULL);
	if (client_slab == NULL)
		goto out;
	openowner_slab = kmem_cache_create("nfsd4_openowners",
			sizeof(struct nfs4_openowner), 0, 0, NULL);
	if (openowner_slab == NULL)
		goto out_free_client_slab;
	lockowner_slab = kmem_cache_create("nfsd4_lockowners",
			sizeof(struct nfs4_lockowner), 0, 0, NULL);
	if (lockowner_slab == NULL)
		goto out_free_openowner_slab;
	file_slab = kmem_cache_create("nfsd4_files",
			sizeof(struct nfs4_file), 0, 0, NULL);
	if (file_slab == NULL)
		goto out_free_lockowner_slab;
	stateid_slab = kmem_cache_create("nfsd4_stateids",
			sizeof(struct nfs4_ol_stateid), 0, 0, NULL);
	if (stateid_slab == NULL)
		goto out_free_file_slab;
	deleg_slab = kmem_cache_create("nfsd4_delegations",
			sizeof(struct nfs4_delegation), 0, 0, NULL);
	if (deleg_slab == NULL)
		goto out_free_stateid_slab;
	odstate_slab = kmem_cache_create("nfsd4_odstate",
			sizeof(struct nfs4_clnt_odstate), 0, 0, NULL);
	if (odstate_slab == NULL)
		goto out_free_deleg_slab;
	return 0;

out_free_deleg_slab:
	kmem_cache_destroy(deleg_slab);
out_free_stateid_slab:
	kmem_cache_destroy(stateid_slab);
out_free_file_slab:
	kmem_cache_destroy(file_slab);
out_free_lockowner_slab:
	kmem_cache_destroy(lockowner_slab);
out_free_openowner_slab:
	kmem_cache_destroy(openowner_slab);
out_free_client_slab:
	kmem_cache_destroy(client_slab);
out:
	dprintk("nfsd4: out of memory while initializing nfsv4\n");
	return -ENOMEM;
}