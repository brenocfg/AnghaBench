#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpc_clnt {int dummy; } ;
struct rpc_auth_create_args {scalar_t__ target_name; int /*<<< orphan*/  pseudoflavor; } ;
struct rpc_auth {int au_cslack; int au_rslack; int au_verfsize; int au_ralign; int /*<<< orphan*/  au_count; int /*<<< orphan*/  au_flags; int /*<<< orphan*/  au_flavor; int /*<<< orphan*/ * au_ops; } ;
struct gss_pipe {int dummy; } ;
struct gss_auth {scalar_t__ service; struct gss_auth* target_name; int /*<<< orphan*/  net; TYPE_1__* mech; struct gss_pipe** gss_pipe; int /*<<< orphan*/  kref; struct rpc_auth rpc_auth; struct rpc_clnt* client; int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;
struct TYPE_5__ {char* gm_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct gss_auth* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GSS_CRED_SLACK ; 
 int GSS_VERF_SLACK ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct gss_pipe*) ; 
 int PTR_ERR (struct gss_pipe*) ; 
 int /*<<< orphan*/  RPCAUTH_AUTH_DATATOUCH ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  authgss_ops ; 
 int /*<<< orphan*/  get_net (int /*<<< orphan*/ ) ; 
 TYPE_1__* gss_mech_get_by_pseudoflavor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_mech_put (TYPE_1__*) ; 
 int /*<<< orphan*/  gss_pipe_free (struct gss_pipe*) ; 
 struct gss_pipe* gss_pipe_get (struct rpc_clnt*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_pseudoflavor_to_datatouch (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ gss_pseudoflavor_to_service (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_upcall_ops_v0 ; 
 int /*<<< orphan*/  gss_upcall_ops_v1 ; 
 int /*<<< orphan*/  gssd_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gss_auth*) ; 
 struct gss_auth* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct gss_auth* kstrdup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rpc_net_ns (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpcauth_destroy_credcache (struct rpc_auth*) ; 
 int rpcauth_init_credcache (struct rpc_auth*) ; 
 int /*<<< orphan*/  trace_rpcgss_createauth (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct gss_auth *
gss_create_new(const struct rpc_auth_create_args *args, struct rpc_clnt *clnt)
{
	rpc_authflavor_t flavor = args->pseudoflavor;
	struct gss_auth *gss_auth;
	struct gss_pipe *gss_pipe;
	struct rpc_auth * auth;
	int err = -ENOMEM; /* XXX? */

	if (!try_module_get(THIS_MODULE))
		return ERR_PTR(err);
	if (!(gss_auth = kmalloc(sizeof(*gss_auth), GFP_KERNEL)))
		goto out_dec;
	INIT_HLIST_NODE(&gss_auth->hash);
	gss_auth->target_name = NULL;
	if (args->target_name) {
		gss_auth->target_name = kstrdup(args->target_name, GFP_KERNEL);
		if (gss_auth->target_name == NULL)
			goto err_free;
	}
	gss_auth->client = clnt;
	gss_auth->net = get_net(rpc_net_ns(clnt));
	err = -EINVAL;
	gss_auth->mech = gss_mech_get_by_pseudoflavor(flavor);
	if (!gss_auth->mech)
		goto err_put_net;
	gss_auth->service = gss_pseudoflavor_to_service(gss_auth->mech, flavor);
	if (gss_auth->service == 0)
		goto err_put_mech;
	if (!gssd_running(gss_auth->net))
		goto err_put_mech;
	auth = &gss_auth->rpc_auth;
	auth->au_cslack = GSS_CRED_SLACK >> 2;
	auth->au_rslack = GSS_VERF_SLACK >> 2;
	auth->au_verfsize = GSS_VERF_SLACK >> 2;
	auth->au_ralign = GSS_VERF_SLACK >> 2;
	auth->au_flags = 0;
	auth->au_ops = &authgss_ops;
	auth->au_flavor = flavor;
	if (gss_pseudoflavor_to_datatouch(gss_auth->mech, flavor))
		auth->au_flags |= RPCAUTH_AUTH_DATATOUCH;
	refcount_set(&auth->au_count, 1);
	kref_init(&gss_auth->kref);

	err = rpcauth_init_credcache(auth);
	if (err)
		goto err_put_mech;
	/*
	 * Note: if we created the old pipe first, then someone who
	 * examined the directory at the right moment might conclude
	 * that we supported only the old pipe.  So we instead create
	 * the new pipe first.
	 */
	gss_pipe = gss_pipe_get(clnt, "gssd", &gss_upcall_ops_v1);
	if (IS_ERR(gss_pipe)) {
		err = PTR_ERR(gss_pipe);
		goto err_destroy_credcache;
	}
	gss_auth->gss_pipe[1] = gss_pipe;

	gss_pipe = gss_pipe_get(clnt, gss_auth->mech->gm_name,
			&gss_upcall_ops_v0);
	if (IS_ERR(gss_pipe)) {
		err = PTR_ERR(gss_pipe);
		goto err_destroy_pipe_1;
	}
	gss_auth->gss_pipe[0] = gss_pipe;

	return gss_auth;
err_destroy_pipe_1:
	gss_pipe_free(gss_auth->gss_pipe[1]);
err_destroy_credcache:
	rpcauth_destroy_credcache(auth);
err_put_mech:
	gss_mech_put(gss_auth->mech);
err_put_net:
	put_net(gss_auth->net);
err_free:
	kfree(gss_auth->target_name);
	kfree(gss_auth);
out_dec:
	module_put(THIS_MODULE);
	trace_rpcgss_createauth(flavor, err);
	return ERR_PTR(err);
}