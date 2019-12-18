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
struct socket {int dummy; } ;
struct rxrpc_call {int /*<<< orphan*/  user_mutex; int /*<<< orphan*/  expect_term_by; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_reduce_call_timer (struct rxrpc_call*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_timer_set_for_hard ; 

void rxrpc_kernel_set_max_life(struct socket *sock, struct rxrpc_call *call,
			       unsigned long hard_timeout)
{
	unsigned long now;

	mutex_lock(&call->user_mutex);

	now = jiffies;
	hard_timeout += now;
	WRITE_ONCE(call->expect_term_by, hard_timeout);
	rxrpc_reduce_call_timer(call, hard_timeout, now, rxrpc_timer_set_for_hard);

	mutex_unlock(&call->user_mutex);
}