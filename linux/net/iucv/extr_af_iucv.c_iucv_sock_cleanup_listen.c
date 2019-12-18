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
struct sock {int /*<<< orphan*/  sk_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IUCV_CLOSED ; 
 struct sock* iucv_accept_dequeue (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iucv_sock_close (struct sock*) ; 
 int /*<<< orphan*/  iucv_sock_kill (struct sock*) ; 

__attribute__((used)) static void iucv_sock_cleanup_listen(struct sock *parent)
{
	struct sock *sk;

	/* Close non-accepted connections */
	while ((sk = iucv_accept_dequeue(parent, NULL))) {
		iucv_sock_close(sk);
		iucv_sock_kill(sk);
	}

	parent->sk_state = IUCV_CLOSED;
}