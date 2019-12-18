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
struct nfs_server {struct nfs_client* nfs_client; } ;
struct nfs_client {int /*<<< orphan*/  cl_lock; } ;
struct nfs4_state_owner {int dummy; } ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct nfs4_state_owner* nfs4_alloc_state_owner (struct nfs_server*,struct cred const*,int /*<<< orphan*/ ) ; 
 struct nfs4_state_owner* nfs4_find_state_owner_locked (struct nfs_server*,struct cred const*) ; 
 int /*<<< orphan*/  nfs4_free_state_owner (struct nfs4_state_owner*) ; 
 int /*<<< orphan*/  nfs4_gc_state_owners (struct nfs_server*) ; 
 struct nfs4_state_owner* nfs4_insert_state_owner_locked (struct nfs4_state_owner*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct nfs4_state_owner *nfs4_get_state_owner(struct nfs_server *server,
					      const struct cred *cred,
					      gfp_t gfp_flags)
{
	struct nfs_client *clp = server->nfs_client;
	struct nfs4_state_owner *sp, *new;

	spin_lock(&clp->cl_lock);
	sp = nfs4_find_state_owner_locked(server, cred);
	spin_unlock(&clp->cl_lock);
	if (sp != NULL)
		goto out;
	new = nfs4_alloc_state_owner(server, cred, gfp_flags);
	if (new == NULL)
		goto out;
	spin_lock(&clp->cl_lock);
	sp = nfs4_insert_state_owner_locked(new);
	spin_unlock(&clp->cl_lock);
	if (sp != new)
		nfs4_free_state_owner(new);
out:
	nfs4_gc_state_owners(server);
	return sp;
}