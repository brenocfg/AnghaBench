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
struct sk_buff {struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ethertype; } ;
struct hippi_hdr {TYPE_1__ snap; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  HIPPI_HLEN ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__be16 hippi_type_trans(struct sk_buff *skb, struct net_device *dev)
{
	struct hippi_hdr *hip;

	/*
	 * This is actually wrong ... question is if we really should
	 * set the raw address here.
	 */
	skb->dev = dev;
	skb_reset_mac_header(skb);
	hip = (struct hippi_hdr *)skb_mac_header(skb);
	skb_pull(skb, HIPPI_HLEN);

	/*
	 * No fancy promisc stuff here now.
	 */

	return hip->snap.ethertype;
}