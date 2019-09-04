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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct in6_addr {int dummy; } ;
struct flowi6 {int flowi6_oif; scalar_t__ fl6_icmp_code; int /*<<< orphan*/  fl6_icmp_type; int /*<<< orphan*/  flowi6_proto; struct in6_addr daddr; struct in6_addr saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_ICMPV6 ; 
 int /*<<< orphan*/  flowi6_to_flowi (struct flowi6*) ; 
 int /*<<< orphan*/  memset (struct flowi6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  security_sk_classify_flow (struct sock*,int /*<<< orphan*/ ) ; 

void icmpv6_flow_init(struct sock *sk, struct flowi6 *fl6,
		      u8 type,
		      const struct in6_addr *saddr,
		      const struct in6_addr *daddr,
		      int oif)
{
	memset(fl6, 0, sizeof(*fl6));
	fl6->saddr = *saddr;
	fl6->daddr = *daddr;
	fl6->flowi6_proto	= IPPROTO_ICMPV6;
	fl6->fl6_icmp_type	= type;
	fl6->fl6_icmp_code	= 0;
	fl6->flowi6_oif		= oif;
	security_sk_classify_flow(sk, flowi6_to_flowi(fl6));
}