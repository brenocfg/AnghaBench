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
struct rocker_tlv {int dummy; } ;
struct rocker_desc_info {int dummy; } ;
struct rocker {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROCKER_TLV_RX_MAX ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* rocker_desc_cookie_ptr_get (struct rocker_desc_info const*) ; 
 int /*<<< orphan*/  rocker_dma_rx_ring_skb_unmap (struct rocker const*,struct rocker_tlv const**) ; 
 int /*<<< orphan*/  rocker_tlv_parse_desc (struct rocker_tlv const**,int /*<<< orphan*/ ,struct rocker_desc_info const*) ; 

__attribute__((used)) static void rocker_dma_rx_ring_skb_free(const struct rocker *rocker,
					const struct rocker_desc_info *desc_info)
{
	const struct rocker_tlv *attrs[ROCKER_TLV_RX_MAX + 1];
	struct sk_buff *skb = rocker_desc_cookie_ptr_get(desc_info);

	if (!skb)
		return;
	rocker_tlv_parse_desc(attrs, ROCKER_TLV_RX_MAX, desc_info);
	rocker_dma_rx_ring_skb_unmap(rocker, attrs);
	dev_kfree_skb_any(skb);
}