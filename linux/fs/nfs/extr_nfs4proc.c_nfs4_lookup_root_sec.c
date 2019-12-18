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
struct rpc_auth_create_args {int /*<<< orphan*/  pseudoflavor; } ;
struct rpc_auth {int dummy; } ;
struct nfs_server {int /*<<< orphan*/  client; } ;
struct nfs_fsinfo {int dummy; } ;
struct nfs_fh {int dummy; } ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;

/* Variables and functions */
 int EACCES ; 
 scalar_t__ IS_ERR (struct rpc_auth*) ; 
 int nfs4_lookup_root (struct nfs_server*,struct nfs_fh*,struct nfs_fsinfo*) ; 
 struct rpc_auth* rpcauth_create (struct rpc_auth_create_args*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs4_lookup_root_sec(struct nfs_server *server, struct nfs_fh *fhandle,
				struct nfs_fsinfo *info, rpc_authflavor_t flavor)
{
	struct rpc_auth_create_args auth_args = {
		.pseudoflavor = flavor,
	};
	struct rpc_auth *auth;

	auth = rpcauth_create(&auth_args, server->client);
	if (IS_ERR(auth))
		return -EACCES;
	return nfs4_lookup_root(server, fhandle, info);
}