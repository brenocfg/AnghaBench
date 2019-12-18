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
struct rpc_clnt {int /*<<< orphan*/  cl_pipedir_objects; } ;
struct net {int dummy; } ;
struct gss_pipe {int /*<<< orphan*/  pipe; int /*<<< orphan*/  pdo; struct rpc_clnt* clnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gss_pipe*) ; 
 int /*<<< orphan*/  rpc_destroy_pipe_data (int /*<<< orphan*/ ) ; 
 struct net* rpc_net_ns (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_remove_pipe_dir_object (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __gss_pipe_free(struct gss_pipe *p)
{
	struct rpc_clnt *clnt = p->clnt;
	struct net *net = rpc_net_ns(clnt);

	rpc_remove_pipe_dir_object(net,
			&clnt->cl_pipedir_objects,
			&p->pdo);
	rpc_destroy_pipe_data(p->pipe);
	kfree(p);
}