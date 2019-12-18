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
struct sock {struct l2tp_tunnel* sk_user_data; } ;
struct l2tp_tunnel {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct l2tp_tunnel *l2tp_tunnel(struct sock *sk)
{
	return sk->sk_user_data;
}