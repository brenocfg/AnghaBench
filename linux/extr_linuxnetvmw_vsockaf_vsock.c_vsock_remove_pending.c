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
struct vsock_sock {int /*<<< orphan*/  pending_links; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

void vsock_remove_pending(struct sock *listener, struct sock *pending)
{
	struct vsock_sock *vpending = vsock_sk(pending);

	list_del_init(&vpending->pending_links);
	sock_put(listener);
	sock_put(pending);
}