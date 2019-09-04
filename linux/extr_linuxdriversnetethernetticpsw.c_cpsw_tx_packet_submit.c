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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct cpsw_priv {scalar_t__ emac_port; struct cpsw_common* cpsw; } ;
struct TYPE_2__ {scalar_t__ dual_emac; } ;
struct cpsw_common {TYPE_1__ data; } ;
struct cpdma_chan {int dummy; } ;

/* Variables and functions */
 int cpdma_chan_submit (struct cpdma_chan*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 

__attribute__((used)) static inline int cpsw_tx_packet_submit(struct cpsw_priv *priv,
					struct sk_buff *skb,
					struct cpdma_chan *txch)
{
	struct cpsw_common *cpsw = priv->cpsw;

	skb_tx_timestamp(skb);
	return cpdma_chan_submit(txch, skb, skb->data, skb->len,
				 priv->emac_port + cpsw->data.dual_emac);
}