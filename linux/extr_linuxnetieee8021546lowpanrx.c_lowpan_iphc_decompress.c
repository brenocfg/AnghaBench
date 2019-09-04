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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct ieee802154_hdr {int /*<<< orphan*/  source; int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ieee802154_hdr_peek_addrs (struct sk_buff*,struct ieee802154_hdr*) ; 
 int lowpan_header_decompress (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int lowpan_iphc_decompress(struct sk_buff *skb)
{
	struct ieee802154_hdr hdr;

	if (ieee802154_hdr_peek_addrs(skb, &hdr) < 0)
		return -EINVAL;

	return lowpan_header_decompress(skb, skb->dev, &hdr.dest, &hdr.source);
}