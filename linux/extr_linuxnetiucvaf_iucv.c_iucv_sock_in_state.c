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
struct sock {int sk_state; } ;

/* Variables and functions */

__attribute__((used)) static int iucv_sock_in_state(struct sock *sk, int state, int state2)
{
	return (sk->sk_state == state || sk->sk_state == state2);
}