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
struct rpc_cred {int /*<<< orphan*/  cl_auth; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_auth; } ;
struct nfs_server {int /*<<< orphan*/  auth_info; } ;
struct nfs4_secinfo_flavors {unsigned int num_flavors; struct nfs4_secinfo4* flavors; } ;
struct nfs4_secinfo4 {int flavor; int /*<<< orphan*/  flavor_info; } ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 struct rpc_cred* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct rpc_cred*) ; 
#define  RPC_AUTH_GSS 130 
 int /*<<< orphan*/  RPC_AUTH_MAXFLAVOR ; 
#define  RPC_AUTH_NULL 129 
#define  RPC_AUTH_UNIX 128 
 int /*<<< orphan*/  nfs_auth_info_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_rpccred (struct rpc_cred*) ; 
 struct rpc_cred* rpc_clone_client_set_auth (struct rpc_cred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_shutdown_client (struct rpc_cred*) ; 
 int /*<<< orphan*/  rpcauth_get_pseudoflavor (int,int /*<<< orphan*/ *) ; 
 struct rpc_cred* rpcauth_lookupcred (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rpc_clnt *nfs_find_best_sec(struct rpc_clnt *clnt,
					  struct nfs_server *server,
					  struct nfs4_secinfo_flavors *flavors)
{
	rpc_authflavor_t pflavor;
	struct nfs4_secinfo4 *secinfo;
	unsigned int i;

	for (i = 0; i < flavors->num_flavors; i++) {
		secinfo = &flavors->flavors[i];

		switch (secinfo->flavor) {
		case RPC_AUTH_NULL:
		case RPC_AUTH_UNIX:
		case RPC_AUTH_GSS:
			pflavor = rpcauth_get_pseudoflavor(secinfo->flavor,
							&secinfo->flavor_info);
			/* does the pseudoflavor match a sec= mount opt? */
			if (pflavor != RPC_AUTH_MAXFLAVOR &&
			    nfs_auth_info_match(&server->auth_info, pflavor)) {
				struct rpc_clnt *new;
				struct rpc_cred *cred;

				/* Cloning creates an rpc_auth for the flavor */
				new = rpc_clone_client_set_auth(clnt, pflavor);
				if (IS_ERR(new))
					continue;
				/**
				* Check that the user actually can use the
				* flavor. This is mostly for RPC_AUTH_GSS
				* where cr_init obtains a gss context
				*/
				cred = rpcauth_lookupcred(new->cl_auth, 0);
				if (IS_ERR(cred)) {
					rpc_shutdown_client(new);
					continue;
				}
				put_rpccred(cred);
				return new;
			}
		}
	}
	return ERR_PTR(-EPERM);
}