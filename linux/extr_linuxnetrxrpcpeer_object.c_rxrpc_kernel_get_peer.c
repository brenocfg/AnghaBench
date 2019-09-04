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
struct socket {int dummy; } ;
struct sockaddr_rxrpc {int dummy; } ;
struct rxrpc_call {TYPE_1__* peer; } ;
struct TYPE_2__ {struct sockaddr_rxrpc srx; } ;

/* Variables and functions */

void rxrpc_kernel_get_peer(struct socket *sock, struct rxrpc_call *call,
			   struct sockaddr_rxrpc *_srx)
{
	*_srx = call->peer->srx;
}