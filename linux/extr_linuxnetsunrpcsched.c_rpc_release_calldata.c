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
struct rpc_call_ops {int /*<<< orphan*/  (* rpc_release ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*) ; 

void rpc_release_calldata(const struct rpc_call_ops *ops, void *calldata)
{
	if (ops->rpc_release != NULL)
		ops->rpc_release(calldata);
}