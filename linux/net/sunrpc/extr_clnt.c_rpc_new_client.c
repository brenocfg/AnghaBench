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
struct rpc_xprt_switch {int dummy; } ;
struct rpc_xprt {struct rpc_timeout* timeout; } ;
struct rpc_version {int /*<<< orphan*/  number; int /*<<< orphan*/  nrprocs; int /*<<< orphan*/  procs; } ;
struct rpc_timeout {int dummy; } ;
struct rpc_program {size_t nrvers; int /*<<< orphan*/  stats; int /*<<< orphan*/  number; struct rpc_version** version; int /*<<< orphan*/  name; } ;
struct rpc_create_args {char* nodename; size_t version; int /*<<< orphan*/  client_name; int /*<<< orphan*/  authflavor; int /*<<< orphan*/ * timeout; scalar_t__ prognumber; int /*<<< orphan*/  cred; int /*<<< orphan*/  servername; struct rpc_program* program; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_cred; int /*<<< orphan*/ * cl_metrics; int /*<<< orphan*/  cl_count; TYPE_1__* cl_timeout; int /*<<< orphan*/  cl_rtt_default; int /*<<< orphan*/ * cl_rtt; int /*<<< orphan*/  cl_xpi; struct rpc_timeout cl_timeout_default; int /*<<< orphan*/  cl_lock; int /*<<< orphan*/  cl_tasks; struct rpc_program const* cl_program; int /*<<< orphan*/  cl_pipedir_objects; int /*<<< orphan*/  cl_stats; int /*<<< orphan*/  cl_vers; int /*<<< orphan*/  cl_prog; int /*<<< orphan*/  cl_maxproc; int /*<<< orphan*/  cl_procinfo; struct rpc_clnt* cl_parent; } ;
struct TYPE_4__ {char* nodename; } ;
struct TYPE_3__ {int /*<<< orphan*/  to_initval; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct rpc_clnt* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpc_xprt*) ; 
 int /*<<< orphan*/  get_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rpc_clnt*) ; 
 struct rpc_clnt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct rpc_timeout*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ ) ; 
 int rpc_alloc_clid (struct rpc_clnt*) ; 
 int /*<<< orphan*/ * rpc_alloc_iostats (struct rpc_clnt*) ; 
 int rpc_client_register (struct rpc_clnt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_clnt_set_nodename (struct rpc_clnt*,char const*) ; 
 int /*<<< orphan*/  rpc_clnt_set_transport (struct rpc_clnt*,struct rpc_xprt*,struct rpc_timeout const*) ; 
 int /*<<< orphan*/  rpc_free_clid (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_free_iostats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_init_pipe_dir_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_init_rtt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpciod_down () ; 
 int rpciod_up () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* utsname () ; 
 int /*<<< orphan*/  xprt_iter_init (int /*<<< orphan*/ *,struct rpc_xprt_switch*) ; 
 int /*<<< orphan*/  xprt_put (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_switch_put (struct rpc_xprt_switch*) ; 

__attribute__((used)) static struct rpc_clnt * rpc_new_client(const struct rpc_create_args *args,
		struct rpc_xprt_switch *xps,
		struct rpc_xprt *xprt,
		struct rpc_clnt *parent)
{
	const struct rpc_program *program = args->program;
	const struct rpc_version *version;
	struct rpc_clnt *clnt = NULL;
	const struct rpc_timeout *timeout;
	const char *nodename = args->nodename;
	int err;

	/* sanity check the name before trying to print it */
	dprintk("RPC:       creating %s client for %s (xprt %p)\n",
			program->name, args->servername, xprt);

	err = rpciod_up();
	if (err)
		goto out_no_rpciod;

	err = -EINVAL;
	if (args->version >= program->nrvers)
		goto out_err;
	version = program->version[args->version];
	if (version == NULL)
		goto out_err;

	err = -ENOMEM;
	clnt = kzalloc(sizeof(*clnt), GFP_KERNEL);
	if (!clnt)
		goto out_err;
	clnt->cl_parent = parent ? : clnt;

	err = rpc_alloc_clid(clnt);
	if (err)
		goto out_no_clid;

	clnt->cl_cred	  = get_cred(args->cred);
	clnt->cl_procinfo = version->procs;
	clnt->cl_maxproc  = version->nrprocs;
	clnt->cl_prog     = args->prognumber ? : program->number;
	clnt->cl_vers     = version->number;
	clnt->cl_stats    = program->stats;
	clnt->cl_metrics  = rpc_alloc_iostats(clnt);
	rpc_init_pipe_dir_head(&clnt->cl_pipedir_objects);
	err = -ENOMEM;
	if (clnt->cl_metrics == NULL)
		goto out_no_stats;
	clnt->cl_program  = program;
	INIT_LIST_HEAD(&clnt->cl_tasks);
	spin_lock_init(&clnt->cl_lock);

	timeout = xprt->timeout;
	if (args->timeout != NULL) {
		memcpy(&clnt->cl_timeout_default, args->timeout,
				sizeof(clnt->cl_timeout_default));
		timeout = &clnt->cl_timeout_default;
	}

	rpc_clnt_set_transport(clnt, xprt, timeout);
	xprt_iter_init(&clnt->cl_xpi, xps);
	xprt_switch_put(xps);

	clnt->cl_rtt = &clnt->cl_rtt_default;
	rpc_init_rtt(&clnt->cl_rtt_default, clnt->cl_timeout->to_initval);

	atomic_set(&clnt->cl_count, 1);

	if (nodename == NULL)
		nodename = utsname()->nodename;
	/* save the nodename */
	rpc_clnt_set_nodename(clnt, nodename);

	err = rpc_client_register(clnt, args->authflavor, args->client_name);
	if (err)
		goto out_no_path;
	if (parent)
		atomic_inc(&parent->cl_count);
	return clnt;

out_no_path:
	rpc_free_iostats(clnt->cl_metrics);
out_no_stats:
	put_cred(clnt->cl_cred);
	rpc_free_clid(clnt);
out_no_clid:
	kfree(clnt);
out_err:
	rpciod_down();
out_no_rpciod:
	xprt_switch_put(xps);
	xprt_put(xprt);
	return ERR_PTR(err);
}