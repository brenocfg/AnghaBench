#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct socket {int dummy; } ;
struct rxrpc_call {TYPE_1__* peer; } ;
struct TYPE_2__ {int /*<<< orphan*/  rtt; } ;

/* Variables and functions */

u64 rxrpc_kernel_get_rtt(struct socket *sock, struct rxrpc_call *call)
{
	return call->peer->rtt;
}