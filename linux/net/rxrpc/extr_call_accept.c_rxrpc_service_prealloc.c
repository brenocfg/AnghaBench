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
struct rxrpc_sock {scalar_t__ discard_new_call; struct rxrpc_backlog* backlog; } ;
struct rxrpc_backlog {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 struct rxrpc_backlog* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_debug_id ; 
 scalar_t__ rxrpc_service_prealloc_one (struct rxrpc_sock*,struct rxrpc_backlog*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rxrpc_service_prealloc(struct rxrpc_sock *rx, gfp_t gfp)
{
	struct rxrpc_backlog *b = rx->backlog;

	if (!b) {
		b = kzalloc(sizeof(struct rxrpc_backlog), gfp);
		if (!b)
			return -ENOMEM;
		rx->backlog = b;
	}

	if (rx->discard_new_call)
		return 0;

	while (rxrpc_service_prealloc_one(rx, b, NULL, NULL, 0, gfp,
					  atomic_inc_return(&rxrpc_debug_id)) == 0)
		;

	return 0;
}