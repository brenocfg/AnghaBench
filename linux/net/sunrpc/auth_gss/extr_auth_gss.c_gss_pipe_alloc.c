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
struct rpc_pipe_ops {int dummy; } ;
struct rpc_clnt {int dummy; } ;
struct gss_pipe {char const* name; int /*<<< orphan*/  pdo; int /*<<< orphan*/  kref; struct rpc_clnt* clnt; int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct gss_pipe* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_PIPE_WAIT_FOR_OPEN ; 
 int /*<<< orphan*/  gss_pipe_dir_object_ops ; 
 int /*<<< orphan*/  kfree (struct gss_pipe*) ; 
 struct gss_pipe* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_init_pipe_dir_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct gss_pipe*) ; 
 int /*<<< orphan*/  rpc_mkpipe_data (struct rpc_pipe_ops const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct gss_pipe *gss_pipe_alloc(struct rpc_clnt *clnt,
		const char *name,
		const struct rpc_pipe_ops *upcall_ops)
{
	struct gss_pipe *p;
	int err = -ENOMEM;

	p = kmalloc(sizeof(*p), GFP_KERNEL);
	if (p == NULL)
		goto err;
	p->pipe = rpc_mkpipe_data(upcall_ops, RPC_PIPE_WAIT_FOR_OPEN);
	if (IS_ERR(p->pipe)) {
		err = PTR_ERR(p->pipe);
		goto err_free_gss_pipe;
	}
	p->name = name;
	p->clnt = clnt;
	kref_init(&p->kref);
	rpc_init_pipe_dir_object(&p->pdo,
			&gss_pipe_dir_object_ops,
			p);
	return p;
err_free_gss_pipe:
	kfree(p);
err:
	return ERR_PTR(err);
}