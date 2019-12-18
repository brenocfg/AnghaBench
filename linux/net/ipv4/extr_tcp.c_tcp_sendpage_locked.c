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
struct sock {int sk_route_caps; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int NETIF_F_SG ; 
 int do_tcp_sendpages (struct sock*,struct page*,int,size_t,int) ; 
 int sock_no_sendpage_locked (struct sock*,struct page*,int,size_t,int) ; 
 int /*<<< orphan*/  tcp_rate_check_app_limited (struct sock*) ; 

int tcp_sendpage_locked(struct sock *sk, struct page *page, int offset,
			size_t size, int flags)
{
	if (!(sk->sk_route_caps & NETIF_F_SG))
		return sock_no_sendpage_locked(sk, page, offset, size, flags);

	tcp_rate_check_app_limited(sk);  /* is sending application-limited? */

	return do_tcp_sendpages(sk, page, offset, size, flags);
}