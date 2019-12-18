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

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dprintk (char*,struct rpc_xprt*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_xprt_free (struct rpc_xprt*) ; 

__attribute__((used)) static void bc_destroy(struct rpc_xprt *xprt)
{
	dprintk("RPC:       bc_destroy xprt %p\n", xprt);

	xs_xprt_free(xprt);
	module_put(THIS_MODULE);
}