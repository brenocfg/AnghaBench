#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_7__ {TYPE_4__ sin_addr; } ;
union sctp_addr {TYPE_3__ v4; } ;
struct TYPE_6__ {int /*<<< orphan*/  freebind; int /*<<< orphan*/  sk; } ;
struct sctp_sock {TYPE_2__ inet; } ;
struct TYPE_5__ {int /*<<< orphan*/  sysctl_ip_nonlocal_bind; } ;
struct net {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 int RTN_LOCAL ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int inet_addr_type (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv6_only_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_opt2sk (struct sctp_sock*) ; 
 struct net* sock_net (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sctp_v4_available(union sctp_addr *addr, struct sctp_sock *sp)
{
	struct net *net = sock_net(&sp->inet.sk);
	int ret = inet_addr_type(net, addr->v4.sin_addr.s_addr);


	if (addr->v4.sin_addr.s_addr != htonl(INADDR_ANY) &&
	   ret != RTN_LOCAL &&
	   !sp->inet.freebind &&
	   !net->ipv4.sysctl_ip_nonlocal_bind)
		return 0;

	if (ipv6_only_sock(sctp_opt2sk(sp)))
		return 0;

	return 1;
}