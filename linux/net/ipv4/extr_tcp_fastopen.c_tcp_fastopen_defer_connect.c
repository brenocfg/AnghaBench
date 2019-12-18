#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct tcp_sock {TYPE_1__* fastopen_req; scalar_t__ fastopen_connect; } ;
struct tcp_fastopen_cookie {int /*<<< orphan*/  len; } ;
struct sock {int /*<<< orphan*/  sk_allocation; } ;
struct TYPE_4__ {int defer_connect; } ;
struct TYPE_3__ {struct tcp_fastopen_cookie cookie; } ;

/* Variables and functions */
 int ENOBUFS ; 
 TYPE_2__* inet_sk (struct sock*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_fastopen_cookie_check (struct sock*,int /*<<< orphan*/ *,struct tcp_fastopen_cookie*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

bool tcp_fastopen_defer_connect(struct sock *sk, int *err)
{
	struct tcp_fastopen_cookie cookie = { .len = 0 };
	struct tcp_sock *tp = tcp_sk(sk);
	u16 mss;

	if (tp->fastopen_connect && !tp->fastopen_req) {
		if (tcp_fastopen_cookie_check(sk, &mss, &cookie)) {
			inet_sk(sk)->defer_connect = 1;
			return true;
		}

		/* Alloc fastopen_req in order for FO option to be included
		 * in SYN
		 */
		tp->fastopen_req = kzalloc(sizeof(*tp->fastopen_req),
					   sk->sk_allocation);
		if (tp->fastopen_req)
			tp->fastopen_req->cookie = cookie;
		else
			*err = -ENOBUFS;
	}
	return false;
}