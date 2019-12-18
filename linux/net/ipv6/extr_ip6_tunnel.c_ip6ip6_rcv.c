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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  ip6ip6_dscp_ecn_decapsulate ; 
 int ipxip6_rcv (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpi_v6 ; 

__attribute__((used)) static int ip6ip6_rcv(struct sk_buff *skb)
{
	return ipxip6_rcv(skb, IPPROTO_IPV6, &tpi_v6,
			  ip6ip6_dscp_ecn_decapsulate);
}