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
struct urb {int transfer_flags; } ;
struct sk_buff {int len; scalar_t__ data; struct p54u_priv* priv; } ;
struct p54u_priv {int /*<<< orphan*/  submitted; int /*<<< orphan*/  udev; } ;
struct p54_hdr {int /*<<< orphan*/  req_id; } ;
struct net2280_tx_hdr {int /*<<< orphan*/  device_addr; void* len; void* val; void* addr; void* port; } ;
struct net2280_reg_write {int /*<<< orphan*/  device_addr; void* len; void* val; void* addr; void* port; } ;
struct ieee80211_hw {int len; scalar_t__ data; struct p54u_priv* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ FREE_AFTER_TX (struct sk_buff*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ISL38XX_DEV_INT_DATA ; 
 int NET2280_DEV_U32 ; 
 int /*<<< orphan*/  P54U_DEV_BASE ; 
 int /*<<< orphan*/  P54U_PIPE_DATA ; 
 int /*<<< orphan*/  P54U_PIPE_DEV ; 
 int URB_FREE_BUFFER ; 
 int URB_ZERO_PACKET ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct net2280_tx_hdr*) ; 
 struct net2280_tx_hdr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct net2280_tx_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p54_free_skb (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  p54u_tx_cb ; 
 int /*<<< orphan*/  p54u_tx_dummy_cb ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net2280_tx_hdr*,int,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static void p54u_tx_net2280(struct ieee80211_hw *dev, struct sk_buff *skb)
{
	struct p54u_priv *priv = dev->priv;
	struct urb *int_urb = NULL, *data_urb = NULL;
	struct net2280_tx_hdr *hdr = (void *)skb->data - sizeof(*hdr);
	struct net2280_reg_write *reg = NULL;
	int err = -ENOMEM;

	reg = kmalloc(sizeof(*reg), GFP_ATOMIC);
	if (!reg)
		goto out;

	int_urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!int_urb)
		goto out;

	data_urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!data_urb)
		goto out;

	reg->port = cpu_to_le16(NET2280_DEV_U32);
	reg->addr = cpu_to_le32(P54U_DEV_BASE);
	reg->val = cpu_to_le32(ISL38XX_DEV_INT_DATA);

	memset(hdr, 0, sizeof(*hdr));
	hdr->len = cpu_to_le16(skb->len);
	hdr->device_addr = ((struct p54_hdr *) skb->data)->req_id;

	usb_fill_bulk_urb(int_urb, priv->udev,
		usb_sndbulkpipe(priv->udev, P54U_PIPE_DEV), reg, sizeof(*reg),
		p54u_tx_dummy_cb, dev);

	/*
	 * URB_FREE_BUFFER triggers a code path in the USB subsystem that will
	 * free what is inside the transfer_buffer after the last reference to
	 * the int_urb is dropped.
	 */
	int_urb->transfer_flags |= URB_FREE_BUFFER | URB_ZERO_PACKET;
	reg = NULL;

	usb_fill_bulk_urb(data_urb, priv->udev,
			  usb_sndbulkpipe(priv->udev, P54U_PIPE_DATA),
			  hdr, skb->len + sizeof(*hdr), FREE_AFTER_TX(skb) ?
			  p54u_tx_cb : p54u_tx_dummy_cb, skb);
	data_urb->transfer_flags |= URB_ZERO_PACKET;

	usb_anchor_urb(int_urb, &priv->submitted);
	err = usb_submit_urb(int_urb, GFP_ATOMIC);
	if (err) {
		usb_unanchor_urb(int_urb);
		goto out;
	}

	usb_anchor_urb(data_urb, &priv->submitted);
	err = usb_submit_urb(data_urb, GFP_ATOMIC);
	if (err) {
		usb_unanchor_urb(data_urb);
		goto out;
	}
out:
	usb_free_urb(int_urb);
	usb_free_urb(data_urb);

	if (err) {
		kfree(reg);
		p54_free_skb(dev, skb);
	}
}