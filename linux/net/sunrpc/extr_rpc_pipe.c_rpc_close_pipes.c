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
struct rpc_pipe {scalar_t__ nreaders; scalar_t__ nwriters; int /*<<< orphan*/  queue_timeout; TYPE_1__* ops; int /*<<< orphan*/  lock; int /*<<< orphan*/ * dentry; scalar_t__ pipelen; int /*<<< orphan*/  pipe; int /*<<< orphan*/  in_upcall; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {struct rpc_pipe* pipe; int /*<<< orphan*/  waitq; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* release_pipe ) (struct inode*) ;int /*<<< orphan*/  destroy_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_2__* RPC_I (struct inode*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_list ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_inode_setowner (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_purge_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct inode*) ; 

__attribute__((used)) static void
rpc_close_pipes(struct inode *inode)
{
	struct rpc_pipe *pipe = RPC_I(inode)->pipe;
	int need_release;
	LIST_HEAD(free_list);

	inode_lock(inode);
	spin_lock(&pipe->lock);
	need_release = pipe->nreaders != 0 || pipe->nwriters != 0;
	pipe->nreaders = 0;
	list_splice_init(&pipe->in_upcall, &free_list);
	list_splice_init(&pipe->pipe, &free_list);
	pipe->pipelen = 0;
	pipe->dentry = NULL;
	spin_unlock(&pipe->lock);
	rpc_purge_list(&RPC_I(inode)->waitq, &free_list, pipe->ops->destroy_msg, -EPIPE);
	pipe->nwriters = 0;
	if (need_release && pipe->ops->release_pipe)
		pipe->ops->release_pipe(inode);
	cancel_delayed_work_sync(&pipe->queue_timeout);
	rpc_inode_setowner(inode, NULL);
	RPC_I(inode)->pipe = NULL;
	inode_unlock(inode);
}