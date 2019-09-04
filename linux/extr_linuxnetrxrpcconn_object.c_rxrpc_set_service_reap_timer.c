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
struct rxrpc_net {int /*<<< orphan*/  service_conn_reap_timer; scalar_t__ live; } ;

/* Variables and functions */
 int /*<<< orphan*/  timer_reduce (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rxrpc_set_service_reap_timer(struct rxrpc_net *rxnet,
					 unsigned long reap_at)
{
	if (rxnet->live)
		timer_reduce(&rxnet->service_conn_reap_timer, reap_at);
}