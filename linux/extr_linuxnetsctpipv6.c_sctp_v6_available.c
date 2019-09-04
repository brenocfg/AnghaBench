#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sin6_addr; } ;
union sctp_addr {TYPE_1__ v6; } ;
struct TYPE_9__ {scalar_t__ freebind; int /*<<< orphan*/  sk; } ;
struct sctp_sock {TYPE_4__ inet; } ;
struct TYPE_7__ {scalar_t__ ip_nonlocal_bind; } ;
struct TYPE_8__ {TYPE_2__ sysctl; } ;
struct net {TYPE_3__ ipv6; } ;
struct in6_addr {int dummy; } ;
struct TYPE_10__ {int (* available ) (union sctp_addr*,struct sctp_sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int IPV6_ADDR_ANY ; 
 int IPV6_ADDR_MAPPED ; 
 int IPV6_ADDR_UNICAST ; 
 int ipv6_addr_type (struct in6_addr const*) ; 
 scalar_t__ ipv6_chk_addr (struct net*,struct in6_addr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv6_only_sock (int /*<<< orphan*/ ) ; 
 TYPE_5__* sctp_get_af_specific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_opt2sk (struct sctp_sock*) ; 
 int /*<<< orphan*/  sctp_v6_map_v4 (union sctp_addr*) ; 
 struct net* sock_net (int /*<<< orphan*/ *) ; 
 int stub1 (union sctp_addr*,struct sctp_sock*) ; 

__attribute__((used)) static int sctp_v6_available(union sctp_addr *addr, struct sctp_sock *sp)
{
	int type;
	struct net *net = sock_net(&sp->inet.sk);
	const struct in6_addr *in6 = (const struct in6_addr *)&addr->v6.sin6_addr;

	type = ipv6_addr_type(in6);
	if (IPV6_ADDR_ANY == type)
		return 1;
	if (type == IPV6_ADDR_MAPPED) {
		if (sp && ipv6_only_sock(sctp_opt2sk(sp)))
			return 0;
		sctp_v6_map_v4(addr);
		return sctp_get_af_specific(AF_INET)->available(addr, sp);
	}
	if (!(type & IPV6_ADDR_UNICAST))
		return 0;

	return sp->inet.freebind || net->ipv6.sysctl.ip_nonlocal_bind ||
		ipv6_chk_addr(net, in6, NULL, 0);
}