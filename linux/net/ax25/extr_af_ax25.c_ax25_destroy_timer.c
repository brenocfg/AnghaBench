#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct sock {int dummy; } ;
struct TYPE_5__ {struct sock* sk; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */
 TYPE_1__* ax25 ; 
 int /*<<< orphan*/  ax25_destroy_socket (TYPE_1__*) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  dtimer ; 
 TYPE_1__* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static void ax25_destroy_timer(struct timer_list *t)
{
	ax25_cb *ax25 = from_timer(ax25, t, dtimer);
	struct sock *sk;

	sk=ax25->sk;

	bh_lock_sock(sk);
	sock_hold(sk);
	ax25_destroy_socket(ax25);
	bh_unlock_sock(sk);
	sock_put(sk);
}