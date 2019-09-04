#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct sock {int /*<<< orphan*/  sk_cookie; } ;
struct TYPE_2__ {int /*<<< orphan*/  cookie_gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ atomic64_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* sock_net (struct sock*) ; 

u64 sock_gen_cookie(struct sock *sk)
{
	while (1) {
		u64 res = atomic64_read(&sk->sk_cookie);

		if (res)
			return res;
		res = atomic64_inc_return(&sock_net(sk)->cookie_gen);
		atomic64_cmpxchg(&sk->sk_cookie, 0, res);
	}
}