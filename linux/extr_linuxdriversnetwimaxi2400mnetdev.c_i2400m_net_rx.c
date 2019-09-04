#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  protocol; struct net_device* dev; scalar_t__ data; } ;
struct TYPE_4__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_2__ stats; } ;
struct TYPE_3__ {struct net_device* net_dev; } ;
struct i2400m {TYPE_1__ wimax_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* __netdev_alloc_skb (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_dump (int,struct device*,void const*,int) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*,void const*,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*,void const*,int) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int /*<<< orphan*/  i2400m_rx_fake_eth_header (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 
 scalar_t__ skb_end_pointer (struct sk_buff*) ; 
 struct sk_buff* skb_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,void const*,int) ; 
 int /*<<< orphan*/  skb_set_mac_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

void i2400m_net_rx(struct i2400m *i2400m, struct sk_buff *skb_rx,
		   unsigned i, const void *buf, int buf_len)
{
	struct net_device *net_dev = i2400m->wimax_dev.net_dev;
	struct device *dev = i2400m_dev(i2400m);
	struct sk_buff *skb;

	d_fnstart(2, dev, "(i2400m %p buf %p buf_len %d)\n",
		  i2400m, buf, buf_len);
	if (i) {
		skb = skb_get(skb_rx);
		d_printf(2, dev, "RX: reusing first payload skb %p\n", skb);
		skb_pull(skb, buf - (void *) skb->data);
		skb_trim(skb, (void *) skb_end_pointer(skb) - buf);
	} else {
		/* Yes, this is bad -- a lot of overhead -- see
		 * comments at the top of the file */
		skb = __netdev_alloc_skb(net_dev, buf_len, GFP_KERNEL);
		if (skb == NULL) {
			dev_err(dev, "NETRX: no memory to realloc skb\n");
			net_dev->stats.rx_dropped++;
			goto error_skb_realloc;
		}
		skb_put_data(skb, buf, buf_len);
	}
	i2400m_rx_fake_eth_header(i2400m->wimax_dev.net_dev,
				  skb->data - ETH_HLEN,
				  cpu_to_be16(ETH_P_IP));
	skb_set_mac_header(skb, -ETH_HLEN);
	skb->dev = i2400m->wimax_dev.net_dev;
	skb->protocol = htons(ETH_P_IP);
	net_dev->stats.rx_packets++;
	net_dev->stats.rx_bytes += buf_len;
	d_printf(3, dev, "NETRX: receiving %d bytes to network stack\n",
		buf_len);
	d_dump(4, dev, buf, buf_len);
	netif_rx_ni(skb);	/* see notes in function header */
error_skb_realloc:
	d_fnend(2, dev, "(i2400m %p buf %p buf_len %d) = void\n",
		i2400m, buf, buf_len);
}