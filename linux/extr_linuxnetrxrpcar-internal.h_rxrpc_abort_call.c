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
typedef  int /*<<< orphan*/  u32 ;
struct rxrpc_call {int /*<<< orphan*/  state_lock; } ;
typedef  int /*<<< orphan*/  rxrpc_seq_t ;

/* Variables and functions */
 int __rxrpc_abort_call (char const*,struct rxrpc_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool rxrpc_abort_call(const char *why, struct rxrpc_call *call,
				    rxrpc_seq_t seq, u32 abort_code, int error)
{
	bool ret;

	write_lock_bh(&call->state_lock);
	ret = __rxrpc_abort_call(why, call, seq, abort_code, error);
	write_unlock_bh(&call->state_lock);
	return ret;
}