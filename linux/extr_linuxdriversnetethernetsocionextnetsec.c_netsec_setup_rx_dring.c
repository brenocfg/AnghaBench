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
struct sk_buff {int dummy; } ;
struct netsec_priv {TYPE_1__* ndev; struct netsec_desc_ring* desc_ring; } ;
struct netsec_desc_ring {int dummy; } ;
struct netsec_desc {scalar_t__ len; } ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int DESC_NUM ; 
 int ENOMEM ; 
 size_t NETSEC_RING_RX ; 
 struct sk_buff* netsec_alloc_skb (struct netsec_priv*,struct netsec_desc*) ; 
 int /*<<< orphan*/  netsec_set_rx_de (struct netsec_priv*,struct netsec_desc_ring*,int,struct netsec_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  netsec_uninit_pkt_dring (struct netsec_priv*,size_t) ; 

__attribute__((used)) static int netsec_setup_rx_dring(struct netsec_priv *priv)
{
	struct netsec_desc_ring *dring = &priv->desc_ring[NETSEC_RING_RX];
	struct netsec_desc desc;
	struct sk_buff *skb;
	int n;

	desc.len = priv->ndev->mtu + 22;

	for (n = 0; n < DESC_NUM; n++) {
		skb = netsec_alloc_skb(priv, &desc);
		if (!skb) {
			netsec_uninit_pkt_dring(priv, NETSEC_RING_RX);
			return -ENOMEM;
		}
		netsec_set_rx_de(priv, dring, n, &desc, skb);
	}

	return 0;
}