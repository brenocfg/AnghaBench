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
struct timer_list {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_timer (struct timer_list*,unsigned long) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 

void sk_reset_timer(struct sock *sk, struct timer_list* timer,
		    unsigned long expires)
{
	if (!mod_timer(timer, expires))
		sock_hold(sk);
}