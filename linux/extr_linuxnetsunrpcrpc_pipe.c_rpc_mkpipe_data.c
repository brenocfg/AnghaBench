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
struct rpc_pipe {int flags; struct rpc_pipe_ops const* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct rpc_pipe* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_pipe (struct rpc_pipe*) ; 
 struct rpc_pipe* kzalloc (int,int /*<<< orphan*/ ) ; 

struct rpc_pipe *rpc_mkpipe_data(const struct rpc_pipe_ops *ops, int flags)
{
	struct rpc_pipe *pipe;

	pipe = kzalloc(sizeof(struct rpc_pipe), GFP_KERNEL);
	if (!pipe)
		return ERR_PTR(-ENOMEM);
	init_pipe(pipe);
	pipe->ops = ops;
	pipe->flags = flags;
	return pipe;
}