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
struct rpc_inode {TYPE_1__* pipe; int /*<<< orphan*/  waitq; } ;
struct poll_table_struct {int dummy; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;
typedef  int __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 struct rpc_inode* RPC_I (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t
rpc_pipe_poll(struct file *filp, struct poll_table_struct *wait)
{
	struct inode *inode = file_inode(filp);
	struct rpc_inode *rpci = RPC_I(inode);
	__poll_t mask = EPOLLOUT | EPOLLWRNORM;

	poll_wait(filp, &rpci->waitq, wait);

	inode_lock(inode);
	if (rpci->pipe == NULL)
		mask |= EPOLLERR | EPOLLHUP;
	else if (filp->private_data || !list_empty(&rpci->pipe->pipe))
		mask |= EPOLLIN | EPOLLRDNORM;
	inode_unlock(inode);
	return mask;
}