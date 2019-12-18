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
struct rpc_pipe {int /*<<< orphan*/ * dentry; int /*<<< orphan*/  lock; int /*<<< orphan*/ * ops; int /*<<< orphan*/  queue_timeout; scalar_t__ pipelen; int /*<<< orphan*/  pipe; int /*<<< orphan*/  in_downcall; int /*<<< orphan*/  in_upcall; scalar_t__ nwriters; scalar_t__ nreaders; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_timeout_upcall_queue ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
init_pipe(struct rpc_pipe *pipe)
{
	pipe->nreaders = 0;
	pipe->nwriters = 0;
	INIT_LIST_HEAD(&pipe->in_upcall);
	INIT_LIST_HEAD(&pipe->in_downcall);
	INIT_LIST_HEAD(&pipe->pipe);
	pipe->pipelen = 0;
	INIT_DELAYED_WORK(&pipe->queue_timeout,
			    rpc_timeout_upcall_queue);
	pipe->ops = NULL;
	spin_lock_init(&pipe->lock);
	pipe->dentry = NULL;
}