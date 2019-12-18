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
struct sk_buff {scalar_t__ mark; scalar_t__ ignore_df; scalar_t__ skb_iif; int /*<<< orphan*/  pkt_type; scalar_t__ tstamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  ipvs_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_reset_ct (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_reset_trace (struct sk_buff*) ; 
 int /*<<< orphan*/  secpath_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 

__attribute__((used)) static void xfrmi_scrub_packet(struct sk_buff *skb, bool xnet)
{
	skb->tstamp = 0;
	skb->pkt_type = PACKET_HOST;
	skb->skb_iif = 0;
	skb->ignore_df = 0;
	skb_dst_drop(skb);
	nf_reset_ct(skb);
	nf_reset_trace(skb);

	if (!xnet)
		return;

	ipvs_reset(skb);
	secpath_reset(skb);
	skb_orphan(skb);
	skb->mark = 0;
}