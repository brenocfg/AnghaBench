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
struct rxrpc_call {int dummy; } ;
struct afs_call {int /*<<< orphan*/ * rxcall; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_put_call (struct afs_call*) ; 

__attribute__((used)) static void afs_rx_discard_new_call(struct rxrpc_call *rxcall,
				    unsigned long user_call_ID)
{
	struct afs_call *call = (struct afs_call *)user_call_ID;

	call->rxcall = NULL;
	afs_put_call(call);
}