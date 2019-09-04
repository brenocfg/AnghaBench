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
struct rpc_cb_add_xprt_calldata {int /*<<< orphan*/  xps; int /*<<< orphan*/  xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rpc_cb_add_xprt_calldata*) ; 
 int /*<<< orphan*/  xprt_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_switch_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpc_cb_add_xprt_release(void *calldata)
{
	struct rpc_cb_add_xprt_calldata *data = calldata;

	xprt_put(data->xprt);
	xprt_switch_put(data->xps);
	kfree(data);
}