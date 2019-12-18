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
struct sk_buff {int len; int /*<<< orphan*/  dev; } ;
struct iphdr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  gateway; } ;
struct TYPE_4__ {TYPE_1__ un; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_MIB_INERRORS ; 
 int /*<<< orphan*/  __ICMP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 TYPE_2__* icmp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  icmp_socket_deliver (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 

__attribute__((used)) static bool icmp_redirect(struct sk_buff *skb)
{
	if (skb->len < sizeof(struct iphdr)) {
		__ICMP_INC_STATS(dev_net(skb->dev), ICMP_MIB_INERRORS);
		return false;
	}

	if (!pskb_may_pull(skb, sizeof(struct iphdr))) {
		/* there aught to be a stat */
		return false;
	}

	icmp_socket_deliver(skb, ntohl(icmp_hdr(skb)->un.gateway));
	return true;
}