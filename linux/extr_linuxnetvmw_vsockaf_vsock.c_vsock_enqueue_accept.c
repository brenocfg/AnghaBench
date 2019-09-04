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
struct vsock_sock {int /*<<< orphan*/  accept_queue; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

void vsock_enqueue_accept(struct sock *listener, struct sock *connected)
{
	struct vsock_sock *vlistener;
	struct vsock_sock *vconnected;

	vlistener = vsock_sk(listener);
	vconnected = vsock_sk(connected);

	sock_hold(connected);
	sock_hold(listener);
	list_add_tail(&vconnected->accept_queue, &vlistener->accept_queue);
}