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
struct rpc_task {int dummy; } ;

/* Variables and functions */
 int xprt_request_retransmit_after_disconnect (struct rpc_task*) ; 

bool
xprt_request_need_retransmit(struct rpc_task *task)
{
	return xprt_request_retransmit_after_disconnect(task);
}