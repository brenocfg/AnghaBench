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
struct socket {int dummy; } ;
struct rxrpc_call {scalar_t__ state; int completion; int error; int /*<<< orphan*/  abort_code; } ;
typedef  enum rxrpc_call_completion { ____Placeholder_rxrpc_call_completion } rxrpc_call_completion ;

/* Variables and functions */
 int EINPROGRESS ; 
 scalar_t__ RXRPC_CALL_COMPLETE ; 
 int /*<<< orphan*/  smp_rmb () ; 

int rxrpc_kernel_check_call(struct socket *sock, struct rxrpc_call *call,
			    enum rxrpc_call_completion *_compl, u32 *_abort_code)
{
	if (call->state != RXRPC_CALL_COMPLETE)
		return -EINPROGRESS;
	smp_rmb();
	*_compl = call->completion;
	*_abort_code = call->abort_code;
	return call->error;
}