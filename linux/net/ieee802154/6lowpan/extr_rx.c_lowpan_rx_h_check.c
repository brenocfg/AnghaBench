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
struct sk_buff {int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ieee802154_get_fc_from_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee802154_is_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802154_skb_is_intra_pan_addressing (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ lowpan_is_nalp (int /*<<< orphan*/ ) ; 
 scalar_t__ lowpan_is_reserved (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_network_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline bool lowpan_rx_h_check(struct sk_buff *skb)
{
	__le16 fc = ieee802154_get_fc_from_skb(skb);

	/* check on ieee802154 conform 6LoWPAN header */
	if (!ieee802154_is_data(fc) ||
	    !ieee802154_skb_is_intra_pan_addressing(fc, skb))
		return false;

	/* check if we can dereference the dispatch */
	if (unlikely(!skb->len))
		return false;

	if (lowpan_is_nalp(*skb_network_header(skb)) ||
	    lowpan_is_reserved(*skb_network_header(skb)))
		return false;

	return true;
}