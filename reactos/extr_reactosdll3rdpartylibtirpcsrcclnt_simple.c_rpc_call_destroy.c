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
struct rpc_call_private {scalar_t__ client; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_DESTROY (scalar_t__) ; 
 int /*<<< orphan*/  free (struct rpc_call_private*) ; 

__attribute__((used)) static void
rpc_call_destroy(void *vp)
{
	struct rpc_call_private *rcp = (struct rpc_call_private *)vp;

	if (rcp) {
		if (rcp->client)
			CLNT_DESTROY(rcp->client);
		free(rcp);
	}
}