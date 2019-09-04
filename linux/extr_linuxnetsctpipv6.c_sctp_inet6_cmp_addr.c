#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ s_addr; } ;
struct TYPE_6__ {TYPE_2__ sin_addr; } ;
struct TYPE_4__ {scalar_t__ sa_family; } ;
union sctp_addr {TYPE_3__ v4; TYPE_1__ sa; } ;
struct sock {int dummy; } ;
struct sctp_sock {int dummy; } ;
struct sctp_af {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ __ipv6_only_sock (struct sock*) ; 
 int __sctp_v6_cmp_addr (union sctp_addr const*,union sctp_addr const*) ; 
 struct sctp_af* sctp_get_af_specific (scalar_t__) ; 
 scalar_t__ sctp_is_any (struct sock*,union sctp_addr const*) ; 
 struct sock* sctp_opt2sk (struct sctp_sock*) ; 

__attribute__((used)) static int sctp_inet6_cmp_addr(const union sctp_addr *addr1,
			       const union sctp_addr *addr2,
			       struct sctp_sock *opt)
{
	struct sock *sk = sctp_opt2sk(opt);
	struct sctp_af *af1, *af2;

	af1 = sctp_get_af_specific(addr1->sa.sa_family);
	af2 = sctp_get_af_specific(addr2->sa.sa_family);

	if (!af1 || !af2)
		return 0;

	/* If the socket is IPv6 only, v4 addrs will not match */
	if (__ipv6_only_sock(sk) && af1 != af2)
		return 0;

	/* Today, wildcard AF_INET/AF_INET6. */
	if (sctp_is_any(sk, addr1) || sctp_is_any(sk, addr2))
		return 1;

	if (addr1->sa.sa_family == AF_INET && addr2->sa.sa_family == AF_INET)
		return addr1->v4.sin_addr.s_addr == addr2->v4.sin_addr.s_addr;

	return __sctp_v6_cmp_addr(addr1, addr2);
}