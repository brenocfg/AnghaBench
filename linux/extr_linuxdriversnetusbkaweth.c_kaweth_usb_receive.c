#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct urb {int status; int actual_length; int transfer_buffer_length; struct kaweth_device* context; TYPE_1__* dev; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_6__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_3__ stats; int /*<<< orphan*/  name; } ;
struct kaweth_device {int end; scalar_t__ rx_buf; TYPE_2__* intf; struct net_device* net; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  status; int /*<<< orphan*/  term_wait; } ;
struct device {int dummy; } ;
typedef  int __u16 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int EILSEQ ; 
 int EOVERFLOW ; 
 int EPIPE ; 
 int EPROTO ; 
 int EREMOTEIO ; 
 int ESHUTDOWN ; 
 int ETIME ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_BLOCKED (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  kaweth_resubmit_rx_urb (struct kaweth_device*,int /*<<< orphan*/ ) ; 
 int le16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,scalar_t__,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kaweth_usb_receive(struct urb *urb)
{
	struct device *dev = &urb->dev->dev;
	struct kaweth_device *kaweth = urb->context;
	struct net_device *net = kaweth->net;
	int status = urb->status;
	unsigned long flags;
	int count = urb->actual_length;
	int count2 = urb->transfer_buffer_length;

	__u16 pkt_len = le16_to_cpup((__le16 *)kaweth->rx_buf);

	struct sk_buff *skb;

	if (unlikely(status == -EPIPE)) {
		net->stats.rx_errors++;
		kaweth->end = 1;
		wake_up(&kaweth->term_wait);
		dev_dbg(dev, "Status was -EPIPE.\n");
		return;
	}
	if (unlikely(status == -ECONNRESET || status == -ESHUTDOWN)) {
		/* we are killed - set a flag and wake the disconnect handler */
		kaweth->end = 1;
		wake_up(&kaweth->term_wait);
		dev_dbg(dev, "Status was -ECONNRESET or -ESHUTDOWN.\n");
		return;
	}
	if (unlikely(status == -EPROTO || status == -ETIME ||
		     status == -EILSEQ)) {
		net->stats.rx_errors++;
		dev_dbg(dev, "Status was -EPROTO, -ETIME, or -EILSEQ.\n");
		return;
	}
	if (unlikely(status == -EOVERFLOW)) {
		net->stats.rx_errors++;
		dev_dbg(dev, "Status was -EOVERFLOW.\n");
	}
	spin_lock_irqsave(&kaweth->device_lock, flags);
	if (IS_BLOCKED(kaweth->status)) {
		spin_unlock_irqrestore(&kaweth->device_lock, flags);
		return;
	}
	spin_unlock_irqrestore(&kaweth->device_lock, flags);

	if(status && status != -EREMOTEIO && count != 1) {
		dev_err(&kaweth->intf->dev,
			"%s RX status: %d count: %d packet_len: %d\n",
			net->name, status, count, (int)pkt_len);
		kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
                return;
	}

	if(kaweth->net && (count > 2)) {
		if(pkt_len > (count - 2)) {
			dev_err(&kaweth->intf->dev,
				"Packet length too long for USB frame (pkt_len: %x, count: %x)\n",
				pkt_len, count);
			dev_err(&kaweth->intf->dev, "Packet len & 2047: %x\n",
				pkt_len & 2047);
			dev_err(&kaweth->intf->dev, "Count 2: %x\n", count2);
		        kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
                        return;
                }

		if(!(skb = dev_alloc_skb(pkt_len+2))) {
		        kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
                        return;
		}

		skb_reserve(skb, 2);    /* Align IP on 16 byte boundaries */

		skb_copy_to_linear_data(skb, kaweth->rx_buf + 2, pkt_len);

		skb_put(skb, pkt_len);

		skb->protocol = eth_type_trans(skb, net);

		netif_rx(skb);

		net->stats.rx_packets++;
		net->stats.rx_bytes += pkt_len;
	}

	kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
}