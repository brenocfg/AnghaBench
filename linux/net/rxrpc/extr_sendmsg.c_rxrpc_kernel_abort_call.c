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
struct rxrpc_call {int /*<<< orphan*/  user_mutex; int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rxrpc_abort_call (char const*,struct rxrpc_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rxrpc_send_abort_packet (struct rxrpc_call*) ; 

bool rxrpc_kernel_abort_call(struct socket *sock, struct rxrpc_call *call,
			     u32 abort_code, int error, const char *why)
{
	bool aborted;

	_enter("{%d},%d,%d,%s", call->debug_id, abort_code, error, why);

	mutex_lock(&call->user_mutex);

	aborted = rxrpc_abort_call(why, call, 0, abort_code, error);
	if (aborted)
		rxrpc_send_abort_packet(call);

	mutex_unlock(&call->user_mutex);
	return aborted;
}