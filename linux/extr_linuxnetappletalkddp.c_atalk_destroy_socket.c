#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;
struct sock {TYPE_1__ sk_timer; int /*<<< orphan*/  sk_receive_queue; } ;

/* Variables and functions */
 scalar_t__ SOCK_DESTROY_TIME ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  atalk_destroy_timer ; 
 int /*<<< orphan*/  atalk_remove_socket (struct sock*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ sk_has_allocations (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void atalk_destroy_socket(struct sock *sk)
{
	atalk_remove_socket(sk);
	skb_queue_purge(&sk->sk_receive_queue);

	if (sk_has_allocations(sk)) {
		timer_setup(&sk->sk_timer, atalk_destroy_timer, 0);
		sk->sk_timer.expires	= jiffies + SOCK_DESTROY_TIME;
		add_timer(&sk->sk_timer);
	} else
		sock_put(sk);
}