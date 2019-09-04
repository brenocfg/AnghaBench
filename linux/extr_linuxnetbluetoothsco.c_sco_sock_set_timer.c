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
struct sock {int /*<<< orphan*/  sk_timer; int /*<<< orphan*/  sk_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int /*<<< orphan*/ ,long) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void sco_sock_set_timer(struct sock *sk, long timeout)
{
	BT_DBG("sock %p state %d timeout %ld", sk, sk->sk_state, timeout);
	sk_reset_timer(sk, &sk->sk_timer, jiffies + timeout);
}