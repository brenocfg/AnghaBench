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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  s6_addr32; } ;
struct TYPE_4__ {int /*<<< orphan*/  s6_addr32; } ;
struct TYPE_6__ {TYPE_2__ saddr; TYPE_1__ daddr; } ;

/* Variables and functions */
 TYPE_3__* ipv6_hdr (struct sk_buff const*) ; 
 int /*<<< orphan*/  secure_tcpv6_ts_off (struct net const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 tcp_v6_init_ts_off(const struct net *net, const struct sk_buff *skb)
{
	return secure_tcpv6_ts_off(net, ipv6_hdr(skb)->daddr.s6_addr32,
				   ipv6_hdr(skb)->saddr.s6_addr32);
}