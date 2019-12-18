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
struct rpc_pipe_msg {int /*<<< orphan*/  list; int /*<<< orphan*/  errno; } ;
struct rpc_pipe {scalar_t__ nwriters; scalar_t__ nreaders; TYPE_1__* ops; int /*<<< orphan*/  lock; scalar_t__ pipelen; int /*<<< orphan*/  pipe; } ;
struct inode {int dummy; } ;
struct file {int f_mode; struct rpc_pipe_msg* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  waitq; struct rpc_pipe* pipe; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* release_pipe ) (struct inode*) ;int /*<<< orphan*/  (* destroy_msg ) (struct rpc_pipe_msg*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_2__* RPC_I (struct inode*) ; 
 int /*<<< orphan*/  free_list ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_purge_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct rpc_pipe_msg*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rpc_pipe_msg*) ; 
 int /*<<< orphan*/  stub2 (struct inode*) ; 

__attribute__((used)) static int
rpc_pipe_release(struct inode *inode, struct file *filp)
{
	struct rpc_pipe *pipe;
	struct rpc_pipe_msg *msg;
	int last_close;

	inode_lock(inode);
	pipe = RPC_I(inode)->pipe;
	if (pipe == NULL)
		goto out;
	msg = filp->private_data;
	if (msg != NULL) {
		spin_lock(&pipe->lock);
		msg->errno = -EAGAIN;
		list_del_init(&msg->list);
		spin_unlock(&pipe->lock);
		pipe->ops->destroy_msg(msg);
	}
	if (filp->f_mode & FMODE_WRITE)
		pipe->nwriters --;
	if (filp->f_mode & FMODE_READ) {
		pipe->nreaders --;
		if (pipe->nreaders == 0) {
			LIST_HEAD(free_list);
			spin_lock(&pipe->lock);
			list_splice_init(&pipe->pipe, &free_list);
			pipe->pipelen = 0;
			spin_unlock(&pipe->lock);
			rpc_purge_list(&RPC_I(inode)->waitq, &free_list,
					pipe->ops->destroy_msg, -EAGAIN);
		}
	}
	last_close = pipe->nwriters == 0 && pipe->nreaders == 0;
	if (last_close && pipe->ops->release_pipe)
		pipe->ops->release_pipe(inode);
out:
	inode_unlock(inode);
	return 0;
}