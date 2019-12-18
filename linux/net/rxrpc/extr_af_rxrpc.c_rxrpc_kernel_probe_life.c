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
struct rxrpc_call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXRPC_ACK_PING ; 
 int /*<<< orphan*/  rxrpc_propose_ACK (struct rxrpc_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_propose_ack_ping_for_check_life ; 
 int /*<<< orphan*/  rxrpc_send_ack_packet (struct rxrpc_call*,int,int /*<<< orphan*/ *) ; 

void rxrpc_kernel_probe_life(struct socket *sock, struct rxrpc_call *call)
{
	rxrpc_propose_ACK(call, RXRPC_ACK_PING, 0, true, false,
			  rxrpc_propose_ack_ping_for_check_life);
	rxrpc_send_ack_packet(call, true, NULL);
}