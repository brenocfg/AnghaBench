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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_scope_id; scalar_t__ sin6_flowinfo; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_bound_dev_if; int /*<<< orphan*/  sk_v6_daddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  inet_dport; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ipv6_iface_scope_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void inet6_csk_addr2sockaddr(struct sock *sk, struct sockaddr *uaddr)
{
	struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *) uaddr;

	sin6->sin6_family = AF_INET6;
	sin6->sin6_addr = sk->sk_v6_daddr;
	sin6->sin6_port	= inet_sk(sk)->inet_dport;
	/* We do not store received flowlabel for TCP */
	sin6->sin6_flowinfo = 0;
	sin6->sin6_scope_id = ipv6_iface_scope_id(&sin6->sin6_addr,
						  sk->sk_bound_dev_if);
}