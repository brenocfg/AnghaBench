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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 TYPE_1__* udp_hdr (struct sk_buff*) ; 

__attribute__((used)) static void udp6_csum_zero_error(struct sk_buff *skb)
{
	/* RFC 2460 section 8.1 says that we SHOULD log
	 * this error. Well, it is reasonable.
	 */
	net_dbg_ratelimited("IPv6: udp checksum is 0 for [%pI6c]:%u->[%pI6c]:%u\n",
			    &ipv6_hdr(skb)->saddr, ntohs(udp_hdr(skb)->source),
			    &ipv6_hdr(skb)->daddr, ntohs(udp_hdr(skb)->dest));
}