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
struct rpc_pipe_msg {scalar_t__ len; int /*<<< orphan*/  list; } ;
struct rpc_pipe {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  dentry; int /*<<< orphan*/  pipelen; int /*<<< orphan*/  pipe; int /*<<< orphan*/  queue_timeout; scalar_t__ nreaders; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  waitq; } ;

/* Variables and functions */
 int EPIPE ; 
 TYPE_1__* RPC_I (int /*<<< orphan*/ ) ; 
 int RPC_PIPE_WAIT_FOR_OPEN ; 
 int /*<<< orphan*/  RPC_UPCALL_TIMEOUT ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpciod_workqueue ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int
rpc_queue_upcall(struct rpc_pipe *pipe, struct rpc_pipe_msg *msg)
{
	int res = -EPIPE;
	struct dentry *dentry;

	spin_lock(&pipe->lock);
	if (pipe->nreaders) {
		list_add_tail(&msg->list, &pipe->pipe);
		pipe->pipelen += msg->len;
		res = 0;
	} else if (pipe->flags & RPC_PIPE_WAIT_FOR_OPEN) {
		if (list_empty(&pipe->pipe))
			queue_delayed_work(rpciod_workqueue,
					&pipe->queue_timeout,
					RPC_UPCALL_TIMEOUT);
		list_add_tail(&msg->list, &pipe->pipe);
		pipe->pipelen += msg->len;
		res = 0;
	}
	dentry = dget(pipe->dentry);
	spin_unlock(&pipe->lock);
	if (dentry) {
		wake_up(&RPC_I(d_inode(dentry))->waitq);
		dput(dentry);
	}
	return res;
}