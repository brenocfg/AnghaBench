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
 unsigned int atomic_fetch_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct rxrpc_local* rxrpc_get_local_maybe (struct rxrpc_local*) ; 
 int /*<<< orphan*/  rxrpc_put_local (struct rxrpc_local*) ; 

struct rxrpc_local *rxrpc_use_local(struct rxrpc_local *local)
{
	unsigned int au;

	local = rxrpc_get_local_maybe(local);
	if (!local)
		return NULL;

	au = atomic_fetch_add_unless(&local->active_users, 1, 0);
	if (au == 0) {
		rxrpc_put_local(local);
		return NULL;
	}

	return local;
}