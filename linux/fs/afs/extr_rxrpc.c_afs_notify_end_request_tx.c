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
struct sock {int dummy; } ;
struct rxrpc_call {int dummy; } ;
struct afs_call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_CALL_CL_AWAIT_REPLY ; 
 int /*<<< orphan*/  AFS_CALL_CL_REQUESTING ; 
 int /*<<< orphan*/  afs_set_call_state (struct afs_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void afs_notify_end_request_tx(struct sock *sock,
				      struct rxrpc_call *rxcall,
				      unsigned long call_user_ID)
{
	struct afs_call *call = (struct afs_call *)call_user_ID;

	afs_set_call_state(call, AFS_CALL_CL_REQUESTING, AFS_CALL_CL_AWAIT_REPLY);
}