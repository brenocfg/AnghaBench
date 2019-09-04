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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct w5100_priv {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {scalar_t__ rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  S0_CR_RECV ; 
 int /*<<< orphan*/  W5100_S0_RX_RD (struct w5100_priv*) ; 
 int /*<<< orphan*/  W5100_S0_RX_RSR (struct w5100_priv*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,scalar_t__) ; 
 struct w5100_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  w5100_command (struct w5100_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ w5100_read16 (struct w5100_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w5100_readbuf (struct w5100_priv*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  w5100_write16 (struct w5100_priv*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *w5100_rx_skb(struct net_device *ndev)
{
	struct w5100_priv *priv = netdev_priv(ndev);
	struct sk_buff *skb;
	u16 rx_len;
	u16 offset;
	u8 header[2];
	u16 rx_buf_len = w5100_read16(priv, W5100_S0_RX_RSR(priv));

	if (rx_buf_len == 0)
		return NULL;

	offset = w5100_read16(priv, W5100_S0_RX_RD(priv));
	w5100_readbuf(priv, offset, header, 2);
	rx_len = get_unaligned_be16(header) - 2;

	skb = netdev_alloc_skb_ip_align(ndev, rx_len);
	if (unlikely(!skb)) {
		w5100_write16(priv, W5100_S0_RX_RD(priv), offset + rx_buf_len);
		w5100_command(priv, S0_CR_RECV);
		ndev->stats.rx_dropped++;
		return NULL;
	}

	skb_put(skb, rx_len);
	w5100_readbuf(priv, offset + 2, skb->data, rx_len);
	w5100_write16(priv, W5100_S0_RX_RD(priv), offset + 2 + rx_len);
	w5100_command(priv, S0_CR_RECV);
	skb->protocol = eth_type_trans(skb, ndev);

	ndev->stats.rx_packets++;
	ndev->stats.rx_bytes += rx_len;

	return skb;
}