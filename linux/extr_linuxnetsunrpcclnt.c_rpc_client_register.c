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
struct super_block {int dummy; } ;
struct rpc_clnt {int dummy; } ;
struct rpc_auth_create_args {char const* target_name; int /*<<< orphan*/  pseudoflavor; } ;
struct rpc_auth {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rpc_auth*) ; 
 int PTR_ERR (struct rpc_auth*) ; 
 int /*<<< orphan*/  __rpc_clnt_remove_pipedir (struct rpc_clnt*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_clnt_debugfs_register (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_clnt_debugfs_unregister (struct rpc_clnt*) ; 
 struct super_block* rpc_get_sb_net (struct net*) ; 
 struct net* rpc_net_ns (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_put_sb_net (struct net*) ; 
 int /*<<< orphan*/  rpc_register_client (struct rpc_clnt*) ; 
 int rpc_setup_pipedir (struct super_block*,struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_unregister_client (struct rpc_clnt*) ; 
 struct rpc_auth* rpcauth_create (struct rpc_auth_create_args*,struct rpc_clnt*) ; 

__attribute__((used)) static int rpc_client_register(struct rpc_clnt *clnt,
			       rpc_authflavor_t pseudoflavor,
			       const char *client_name)
{
	struct rpc_auth_create_args auth_args = {
		.pseudoflavor = pseudoflavor,
		.target_name = client_name,
	};
	struct rpc_auth *auth;
	struct net *net = rpc_net_ns(clnt);
	struct super_block *pipefs_sb;
	int err;

	rpc_clnt_debugfs_register(clnt);

	pipefs_sb = rpc_get_sb_net(net);
	if (pipefs_sb) {
		err = rpc_setup_pipedir(pipefs_sb, clnt);
		if (err)
			goto out;
	}

	rpc_register_client(clnt);
	if (pipefs_sb)
		rpc_put_sb_net(net);

	auth = rpcauth_create(&auth_args, clnt);
	if (IS_ERR(auth)) {
		dprintk("RPC:       Couldn't create auth handle (flavor %u)\n",
				pseudoflavor);
		err = PTR_ERR(auth);
		goto err_auth;
	}
	return 0;
err_auth:
	pipefs_sb = rpc_get_sb_net(net);
	rpc_unregister_client(clnt);
	__rpc_clnt_remove_pipedir(clnt);
out:
	if (pipefs_sb)
		rpc_put_sb_net(net);
	rpc_clnt_debugfs_unregister(clnt);
	return err;
}