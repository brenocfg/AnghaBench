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
struct rxrpc_call {int tx_total_len; } ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 

void rxrpc_kernel_set_tx_length(struct socket *sock, struct rxrpc_call *call,
				s64 tx_total_len)
{
	WARN_ON(call->tx_total_len != -1);
	call->tx_total_len = tx_total_len;
}