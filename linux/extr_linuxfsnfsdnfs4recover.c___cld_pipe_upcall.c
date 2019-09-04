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
struct rpc_pipe_msg {int len; int errno; struct cld_msg* data; } ;
struct rpc_pipe {int dummy; } ;
struct cld_msg {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  memset (struct rpc_pipe_msg*,int /*<<< orphan*/ ,int) ; 
 int rpc_queue_upcall (struct rpc_pipe*,struct rpc_pipe_msg*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__cld_pipe_upcall(struct rpc_pipe *pipe, struct cld_msg *cmsg)
{
	int ret;
	struct rpc_pipe_msg msg;

	memset(&msg, 0, sizeof(msg));
	msg.data = cmsg;
	msg.len = sizeof(*cmsg);

	/*
	 * Set task state before we queue the upcall. That prevents
	 * wake_up_process in the downcall from racing with schedule.
	 */
	set_current_state(TASK_UNINTERRUPTIBLE);
	ret = rpc_queue_upcall(pipe, &msg);
	if (ret < 0) {
		set_current_state(TASK_RUNNING);
		goto out;
	}

	schedule();

	if (msg.errno < 0)
		ret = msg.errno;
out:
	return ret;
}