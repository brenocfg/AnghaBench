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
struct xprt_create {int dummy; } ;
struct rpc_xprt_switch {int dummy; } ;
struct rpc_xprt {int dummy; } ;
struct rpc_timeout {int dummy; } ;
struct rpc_clnt {struct rpc_clnt* cl_parent; int /*<<< orphan*/  cl_xpi; struct rpc_timeout* cl_timeout; TYPE_1__* cl_auth; } ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;
struct TYPE_2__ {int /*<<< orphan*/  au_flavor; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct rpc_xprt*) ; 
 int PTR_ERR (struct rpc_xprt*) ; 
 int /*<<< orphan*/  __rpc_clnt_remove_pipedir (struct rpc_clnt*) ; 
 int /*<<< orphan*/  dprintk (char*,struct rpc_clnt*) ; 
 int rpc_client_register (struct rpc_clnt*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_clnt_debugfs_unregister (struct rpc_clnt*) ; 
 struct rpc_xprt* rpc_clnt_set_transport (struct rpc_clnt*,struct rpc_xprt*,struct rpc_timeout const*) ; 
 int /*<<< orphan*/  rpc_release_client (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_unregister_client (struct rpc_clnt*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 struct rpc_xprt* xprt_create_transport (struct xprt_create*) ; 
 struct rpc_xprt_switch* xprt_iter_xchg_switch (int /*<<< orphan*/ *,struct rpc_xprt_switch*) ; 
 int /*<<< orphan*/  xprt_put (struct rpc_xprt*) ; 
 struct rpc_xprt_switch* xprt_switch_alloc (struct rpc_xprt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_switch_put (struct rpc_xprt_switch*) ; 

int rpc_switch_client_transport(struct rpc_clnt *clnt,
		struct xprt_create *args,
		const struct rpc_timeout *timeout)
{
	const struct rpc_timeout *old_timeo;
	rpc_authflavor_t pseudoflavor;
	struct rpc_xprt_switch *xps, *oldxps;
	struct rpc_xprt *xprt, *old;
	struct rpc_clnt *parent;
	int err;

	xprt = xprt_create_transport(args);
	if (IS_ERR(xprt)) {
		dprintk("RPC:       failed to create new xprt for clnt %p\n",
			clnt);
		return PTR_ERR(xprt);
	}

	xps = xprt_switch_alloc(xprt, GFP_KERNEL);
	if (xps == NULL) {
		xprt_put(xprt);
		return -ENOMEM;
	}

	pseudoflavor = clnt->cl_auth->au_flavor;

	old_timeo = clnt->cl_timeout;
	old = rpc_clnt_set_transport(clnt, xprt, timeout);
	oldxps = xprt_iter_xchg_switch(&clnt->cl_xpi, xps);

	rpc_unregister_client(clnt);
	__rpc_clnt_remove_pipedir(clnt);
	rpc_clnt_debugfs_unregister(clnt);

	/*
	 * A new transport was created.  "clnt" therefore
	 * becomes the root of a new cl_parent tree.  clnt's
	 * children, if it has any, still point to the old xprt.
	 */
	parent = clnt->cl_parent;
	clnt->cl_parent = clnt;

	/*
	 * The old rpc_auth cache cannot be re-used.  GSS
	 * contexts in particular are between a single
	 * client and server.
	 */
	err = rpc_client_register(clnt, pseudoflavor, NULL);
	if (err)
		goto out_revert;

	synchronize_rcu();
	if (parent != clnt)
		rpc_release_client(parent);
	xprt_switch_put(oldxps);
	xprt_put(old);
	dprintk("RPC:       replaced xprt for clnt %p\n", clnt);
	return 0;

out_revert:
	xps = xprt_iter_xchg_switch(&clnt->cl_xpi, oldxps);
	rpc_clnt_set_transport(clnt, old, old_timeo);
	clnt->cl_parent = parent;
	rpc_client_register(clnt, pseudoflavor, NULL);
	xprt_switch_put(xps);
	xprt_put(xprt);
	dprintk("RPC:       failed to switch xprt for clnt %p\n", clnt);
	return err;
}