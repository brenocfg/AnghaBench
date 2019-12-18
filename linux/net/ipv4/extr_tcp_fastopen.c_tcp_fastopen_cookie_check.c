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
typedef  int /*<<< orphan*/  u16 ;
struct tcp_fastopen_cookie {int len; } ;
struct sock {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TFO_CLIENT_NO_COOKIE ; 
 struct dst_entry* __sk_dst_get (struct sock*) ; 
 scalar_t__ tcp_fastopen_active_should_disable (struct sock*) ; 
 int /*<<< orphan*/  tcp_fastopen_cache_get (struct sock*,int /*<<< orphan*/ *,struct tcp_fastopen_cookie*) ; 
 scalar_t__ tcp_fastopen_no_cookie (struct sock*,struct dst_entry const*,int /*<<< orphan*/ ) ; 

bool tcp_fastopen_cookie_check(struct sock *sk, u16 *mss,
			       struct tcp_fastopen_cookie *cookie)
{
	const struct dst_entry *dst;

	tcp_fastopen_cache_get(sk, mss, cookie);

	/* Firewall blackhole issue check */
	if (tcp_fastopen_active_should_disable(sk)) {
		cookie->len = -1;
		return false;
	}

	dst = __sk_dst_get(sk);

	if (tcp_fastopen_no_cookie(sk, dst, TFO_CLIENT_NO_COOKIE)) {
		cookie->len = -1;
		return true;
	}
	return cookie->len > 0;
}