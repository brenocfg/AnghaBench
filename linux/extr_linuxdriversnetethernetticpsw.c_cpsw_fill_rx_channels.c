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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct cpsw_priv {int /*<<< orphan*/  ndev; struct cpsw_common* cpsw; } ;
struct cpsw_common {int rx_ch_num; TYPE_1__* rxv; int /*<<< orphan*/  rx_packet_max; } ;
struct TYPE_2__ {int /*<<< orphan*/  ch; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* __netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cpdma_chan_get_rx_buf_num (int /*<<< orphan*/ ) ; 
 int cpdma_chan_submit (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_err (struct cpsw_priv*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cpsw_info (struct cpsw_priv*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kmemleak_not_leak (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static int cpsw_fill_rx_channels(struct cpsw_priv *priv)
{
	struct cpsw_common *cpsw = priv->cpsw;
	struct sk_buff *skb;
	int ch_buf_num;
	int ch, i, ret;

	for (ch = 0; ch < cpsw->rx_ch_num; ch++) {
		ch_buf_num = cpdma_chan_get_rx_buf_num(cpsw->rxv[ch].ch);
		for (i = 0; i < ch_buf_num; i++) {
			skb = __netdev_alloc_skb_ip_align(priv->ndev,
							  cpsw->rx_packet_max,
							  GFP_KERNEL);
			if (!skb) {
				cpsw_err(priv, ifup, "cannot allocate skb\n");
				return -ENOMEM;
			}

			skb_set_queue_mapping(skb, ch);
			ret = cpdma_chan_submit(cpsw->rxv[ch].ch, skb,
						skb->data, skb_tailroom(skb),
						0);
			if (ret < 0) {
				cpsw_err(priv, ifup,
					 "cannot submit skb to channel %d rx, error %d\n",
					 ch, ret);
				kfree_skb(skb);
				return ret;
			}
			kmemleak_not_leak(skb);
		}

		cpsw_info(priv, ifup, "ch %d rx, submitted %d descriptors\n",
			  ch, ch_buf_num);
	}

	return 0;
}