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
struct nfs_server {struct nfs_server* client_acl; } ;
struct nfs_fh {int dummy; } ;
struct nfs_fattr {int dummy; } ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct nfs_server*) ; 
 struct nfs_server* nfs_clone_server (struct nfs_server*,struct nfs_fh*,struct nfs_fattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_init_server_aclclient (struct nfs_server*) ; 

struct nfs_server *nfs3_clone_server(struct nfs_server *source,
				     struct nfs_fh *fh,
				     struct nfs_fattr *fattr,
				     rpc_authflavor_t flavor)
{
	struct nfs_server *server = nfs_clone_server(source, fh, fattr, flavor);
	if (!IS_ERR(server) && !IS_ERR(source->client_acl))
		nfs_init_server_aclclient(server);
	return server;
}