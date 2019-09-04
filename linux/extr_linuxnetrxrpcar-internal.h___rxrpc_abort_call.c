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
struct rxrpc_call {int /*<<< orphan*/  call_id; int /*<<< orphan*/  cid; int /*<<< orphan*/  debug_id; } ;
typedef  int /*<<< orphan*/  rxrpc_seq_t ;

/* Variables and functions */
 int /*<<< orphan*/  RXRPC_CALL_LOCALLY_ABORTED ; 
 int __rxrpc_set_call_completion (struct rxrpc_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_rxrpc_abort (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool __rxrpc_abort_call(const char *why, struct rxrpc_call *call,
				      rxrpc_seq_t seq,
				      u32 abort_code, int error)
{
	trace_rxrpc_abort(call->debug_id, why, call->cid, call->call_id, seq,
			  abort_code, error);
	return __rxrpc_set_call_completion(call, RXRPC_CALL_LOCALLY_ABORTED,
					   abort_code, error);
}