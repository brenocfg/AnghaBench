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
struct nfs_client_initdata {int /*<<< orphan*/  net; int /*<<< orphan*/  nconnect; int /*<<< orphan*/  proto; scalar_t__ hostname; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; TYPE_1__* nfs_mod; } ;
struct nfs_client {char* cl_principal; TYPE_1__* cl_nfs_mod; int /*<<< orphan*/  cl_net; int /*<<< orphan*/  cl_nconnect; int /*<<< orphan*/  cl_proto; struct nfs_client* cl_rpcclient; int /*<<< orphan*/  cl_superblocks; int /*<<< orphan*/  cl_hostname; int /*<<< orphan*/  cl_addrlen; int /*<<< orphan*/  cl_addr; int /*<<< orphan*/  cl_cons_state; int /*<<< orphan*/  cl_count; int /*<<< orphan*/  rpc_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  rpc_ops; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct nfs_client* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS_CS_INITING ; 
 int /*<<< orphan*/  get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfs_client*) ; 
 int /*<<< orphan*/  kstrdup (scalar_t__,int /*<<< orphan*/ ) ; 
 struct nfs_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_fscache_get_client_cookie (struct nfs_client*) ; 
 int /*<<< orphan*/  put_nfs_version (TYPE_1__*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct nfs_client *nfs_alloc_client(const struct nfs_client_initdata *cl_init)
{
	struct nfs_client *clp;
	int err = -ENOMEM;

	if ((clp = kzalloc(sizeof(*clp), GFP_KERNEL)) == NULL)
		goto error_0;

	clp->cl_nfs_mod = cl_init->nfs_mod;
	if (!try_module_get(clp->cl_nfs_mod->owner))
		goto error_dealloc;

	clp->rpc_ops = clp->cl_nfs_mod->rpc_ops;

	refcount_set(&clp->cl_count, 1);
	clp->cl_cons_state = NFS_CS_INITING;

	memcpy(&clp->cl_addr, cl_init->addr, cl_init->addrlen);
	clp->cl_addrlen = cl_init->addrlen;

	if (cl_init->hostname) {
		err = -ENOMEM;
		clp->cl_hostname = kstrdup(cl_init->hostname, GFP_KERNEL);
		if (!clp->cl_hostname)
			goto error_cleanup;
	}

	INIT_LIST_HEAD(&clp->cl_superblocks);
	clp->cl_rpcclient = ERR_PTR(-EINVAL);

	clp->cl_proto = cl_init->proto;
	clp->cl_nconnect = cl_init->nconnect;
	clp->cl_net = get_net(cl_init->net);

	clp->cl_principal = "*";
	nfs_fscache_get_client_cookie(clp);

	return clp;

error_cleanup:
	put_nfs_version(clp->cl_nfs_mod);
error_dealloc:
	kfree(clp);
error_0:
	return ERR_PTR(err);
}