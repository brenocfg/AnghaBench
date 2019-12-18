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
struct rpc_xprt {int dummy; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_xpi; } ;

/* Variables and functions */
 struct rpc_xprt* rpc_task_get_xprt (struct rpc_clnt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_iter_get_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rpc_xprt *
rpc_task_get_next_xprt(struct rpc_clnt *clnt)
{
	return rpc_task_get_xprt(clnt, xprt_iter_get_next(&clnt->cl_xpi));
}