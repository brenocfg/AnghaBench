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
typedef  scalar_t__ u64 ;
struct sock {int /*<<< orphan*/  sk_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ atomic64_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cookie_gen ; 

u64 sock_gen_cookie(struct sock *sk)
{
	while (1) {
		u64 res = atomic64_read(&sk->sk_cookie);

		if (res)
			return res;
		res = atomic64_inc_return(&cookie_gen);
		atomic64_cmpxchg(&sk->sk_cookie, 0, res);
	}
}