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
struct tcp_ulp_ops {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int __tcp_set_ulp (struct sock*,struct tcp_ulp_ops const*) ; 
 struct tcp_ulp_ops* __tcp_ulp_find_autoload (char const*) ; 
 int /*<<< orphan*/  sock_owned_by_me (struct sock*) ; 

int tcp_set_ulp(struct sock *sk, const char *name)
{
	const struct tcp_ulp_ops *ulp_ops;

	sock_owned_by_me(sk);

	ulp_ops = __tcp_ulp_find_autoload(name);
	if (!ulp_ops)
		return -ENOENT;

	return __tcp_set_ulp(sk, ulp_ops);
}