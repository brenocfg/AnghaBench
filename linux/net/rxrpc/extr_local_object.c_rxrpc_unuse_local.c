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
struct rxrpc_local {int /*<<< orphan*/  active_users; } ;

/* Variables and functions */
 unsigned int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_put_local (struct rxrpc_local*) ; 
 int /*<<< orphan*/  rxrpc_queue_local (struct rxrpc_local*) ; 

void rxrpc_unuse_local(struct rxrpc_local *local)
{
	unsigned int au;

	if (local) {
		au = atomic_dec_return(&local->active_users);
		if (au == 0)
			rxrpc_queue_local(local);
		else
			rxrpc_put_local(local);
	}
}