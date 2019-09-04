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
struct sk_buff {int encapsulation; scalar_t__ ip_summed; } ;
struct TYPE_2__ {int gso_type; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_NONE ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ likely (int) ; 
 int skb_header_unclone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_inner_headers (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int iptunnel_handle_offloads(struct sk_buff *skb,
			     int gso_type_mask)
{
	int err;

	if (likely(!skb->encapsulation)) {
		skb_reset_inner_headers(skb);
		skb->encapsulation = 1;
	}

	if (skb_is_gso(skb)) {
		err = skb_header_unclone(skb, GFP_ATOMIC);
		if (unlikely(err))
			return err;
		skb_shinfo(skb)->gso_type |= gso_type_mask;
		return 0;
	}

	if (skb->ip_summed != CHECKSUM_PARTIAL) {
		skb->ip_summed = CHECKSUM_NONE;
		/* We clear encapsulation here to prevent badly-written
		 * drivers potentially deciding to offload an inner checksum
		 * if we set CHECKSUM_PARTIAL on the outer header.
		 * This should go away when the drivers are all fixed.
		 */
		skb->encapsulation = 0;
	}

	return 0;
}