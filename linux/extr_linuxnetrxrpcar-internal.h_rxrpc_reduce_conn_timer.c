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
struct rxrpc_connection {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  timer_reduce (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void rxrpc_reduce_conn_timer(struct rxrpc_connection *conn,
					   unsigned long expire_at)
{
	timer_reduce(&conn->timer, expire_at);
}