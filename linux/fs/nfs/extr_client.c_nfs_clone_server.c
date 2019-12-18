#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs_server {scalar_t__ namelen; int /*<<< orphan*/  mount_time; TYPE_2__* client; int /*<<< orphan*/  fsid; TYPE_1__* nfs_client; int /*<<< orphan*/  destroy; int /*<<< orphan*/  cred; } ;
struct nfs_fh {int dummy; } ;
struct nfs_fattr {int /*<<< orphan*/  fsid; } ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;
struct TYPE_4__ {int /*<<< orphan*/  cl_timeout; } ;
struct TYPE_3__ {int /*<<< orphan*/  cl_count; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct nfs_server* ERR_PTR (int) ; 
 scalar_t__ NFS4_MAXNAMLEN ; 
 int /*<<< orphan*/  get_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 struct nfs_fattr* nfs_alloc_fattr () ; 
 struct nfs_server* nfs_alloc_server () ; 
 int /*<<< orphan*/  nfs_free_fattr (struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_free_server (struct nfs_server*) ; 
 int nfs_init_server_rpcclient (struct nfs_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs_probe_fsinfo (struct nfs_server*,struct nfs_fh*,struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_server_copy_userdata (struct nfs_server*,struct nfs_server*) ; 
 int /*<<< orphan*/  nfs_server_insert_lists (struct nfs_server*) ; 
 int nfs_start_lockd (struct nfs_server*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

struct nfs_server *nfs_clone_server(struct nfs_server *source,
				    struct nfs_fh *fh,
				    struct nfs_fattr *fattr,
				    rpc_authflavor_t flavor)
{
	struct nfs_server *server;
	struct nfs_fattr *fattr_fsinfo;
	int error;

	server = nfs_alloc_server();
	if (!server)
		return ERR_PTR(-ENOMEM);

	server->cred = get_cred(source->cred);

	error = -ENOMEM;
	fattr_fsinfo = nfs_alloc_fattr();
	if (fattr_fsinfo == NULL)
		goto out_free_server;

	/* Copy data from the source */
	server->nfs_client = source->nfs_client;
	server->destroy = source->destroy;
	refcount_inc(&server->nfs_client->cl_count);
	nfs_server_copy_userdata(server, source);

	server->fsid = fattr->fsid;

	error = nfs_init_server_rpcclient(server,
			source->client->cl_timeout,
			flavor);
	if (error < 0)
		goto out_free_server;

	/* probe the filesystem info for this server filesystem */
	error = nfs_probe_fsinfo(server, fh, fattr_fsinfo);
	if (error < 0)
		goto out_free_server;

	if (server->namelen == 0 || server->namelen > NFS4_MAXNAMLEN)
		server->namelen = NFS4_MAXNAMLEN;

	error = nfs_start_lockd(server);
	if (error < 0)
		goto out_free_server;

	nfs_server_insert_lists(server);
	server->mount_time = jiffies;

	nfs_free_fattr(fattr_fsinfo);
	return server;

out_free_server:
	nfs_free_fattr(fattr_fsinfo);
	nfs_free_server(server);
	return ERR_PTR(error);
}