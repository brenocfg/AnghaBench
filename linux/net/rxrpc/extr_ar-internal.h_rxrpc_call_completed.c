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
struct rxrpc_call {int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 int __rxrpc_call_completed (struct rxrpc_call*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool rxrpc_call_completed(struct rxrpc_call *call)
{
	bool ret;

	write_lock_bh(&call->state_lock);
	ret = __rxrpc_call_completed(call);
	write_unlock_bh(&call->state_lock);
	return ret;
}