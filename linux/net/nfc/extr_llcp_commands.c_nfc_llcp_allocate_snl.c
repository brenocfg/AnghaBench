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
typedef  size_t u16 ;
struct sk_buff {int dummy; } ;
struct nfc_llcp_local {struct nfc_dev* dev; } ;
struct nfc_dev {scalar_t__ tx_headroom; scalar_t__ tx_tailroom; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ LLCP_HEADER_SIZE ; 
 int /*<<< orphan*/  LLCP_PDU_SNL ; 
 int /*<<< orphan*/  LLCP_SAP_SDP ; 
 scalar_t__ NFC_HEADER_SIZE ; 
 struct sk_buff* alloc_skb (size_t,int /*<<< orphan*/ ) ; 
 struct sk_buff* llcp_add_header (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *nfc_llcp_allocate_snl(struct nfc_llcp_local *local,
					     size_t tlv_length)
{
	struct sk_buff *skb;
	struct nfc_dev *dev;
	u16 size = 0;

	if (local == NULL)
		return ERR_PTR(-ENODEV);

	dev = local->dev;
	if (dev == NULL)
		return ERR_PTR(-ENODEV);

	size += LLCP_HEADER_SIZE;
	size += dev->tx_headroom + dev->tx_tailroom + NFC_HEADER_SIZE;
	size += tlv_length;

	skb = alloc_skb(size, GFP_KERNEL);
	if (skb == NULL)
		return ERR_PTR(-ENOMEM);

	skb_reserve(skb, dev->tx_headroom + NFC_HEADER_SIZE);

	skb = llcp_add_header(skb, LLCP_SAP_SDP, LLCP_SAP_SDP, LLCP_PDU_SNL);

	return skb;
}