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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct nfc_llcp_local {int /*<<< orphan*/  tx_queue; struct nfc_dev* dev; } ;
struct nfc_dev {scalar_t__ tx_headroom; scalar_t__ tx_tailroom; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ LLCP_HEADER_SIZE ; 
 int /*<<< orphan*/  LLCP_PDU_DM ; 
 scalar_t__ NFC_HEADER_SIZE ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 struct sk_buff* llcp_add_header (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

int nfc_llcp_send_dm(struct nfc_llcp_local *local, u8 ssap, u8 dsap, u8 reason)
{
	struct sk_buff *skb;
	struct nfc_dev *dev;
	u16 size = 1; /* Reason code */

	pr_debug("Sending DM reason 0x%x\n", reason);

	if (local == NULL)
		return -ENODEV;

	dev = local->dev;
	if (dev == NULL)
		return -ENODEV;

	size += LLCP_HEADER_SIZE;
	size += dev->tx_headroom + dev->tx_tailroom + NFC_HEADER_SIZE;

	skb = alloc_skb(size, GFP_KERNEL);
	if (skb == NULL)
		return -ENOMEM;

	skb_reserve(skb, dev->tx_headroom + NFC_HEADER_SIZE);

	skb = llcp_add_header(skb, dsap, ssap, LLCP_PDU_DM);

	skb_put_data(skb, &reason, 1);

	skb_queue_head(&local->tx_queue, skb);

	return 0;
}