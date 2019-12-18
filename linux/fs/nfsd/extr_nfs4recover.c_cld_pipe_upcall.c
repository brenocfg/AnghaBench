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
struct rpc_pipe {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int __cld_pipe_upcall (struct rpc_pipe*,void*) ; 

__attribute__((used)) static int
cld_pipe_upcall(struct rpc_pipe *pipe, void *cmsg)
{
	int ret;

	/*
	 * -EAGAIN occurs when pipe is closed and reopened while there are
	 *  upcalls queued.
	 */
	do {
		ret = __cld_pipe_upcall(pipe, cmsg);
	} while (ret == -EAGAIN);

	return ret;
}