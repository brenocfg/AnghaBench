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
struct rpc_pipe {scalar_t__ nreaders; scalar_t__ nwriters; TYPE_1__* ops; } ;
struct inode {int dummy; } ;
struct file {int f_mode; } ;
struct TYPE_4__ {struct rpc_pipe* pipe; } ;
struct TYPE_3__ {int (* open_pipe ) (struct inode*) ;} ;

/* Variables and functions */
 int ENXIO ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 TYPE_2__* RPC_I (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int stub1 (struct inode*) ; 

__attribute__((used)) static int
rpc_pipe_open(struct inode *inode, struct file *filp)
{
	struct rpc_pipe *pipe;
	int first_open;
	int res = -ENXIO;

	inode_lock(inode);
	pipe = RPC_I(inode)->pipe;
	if (pipe == NULL)
		goto out;
	first_open = pipe->nreaders == 0 && pipe->nwriters == 0;
	if (first_open && pipe->ops->open_pipe) {
		res = pipe->ops->open_pipe(inode);
		if (res)
			goto out;
	}
	if (filp->f_mode & FMODE_READ)
		pipe->nreaders++;
	if (filp->f_mode & FMODE_WRITE)
		pipe->nwriters++;
	res = 0;
out:
	inode_unlock(inode);
	return res;
}