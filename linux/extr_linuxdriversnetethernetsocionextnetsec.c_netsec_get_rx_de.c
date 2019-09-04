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
struct netsec_rx_pkt_info {int err_flag; int rx_cksum_result; int err_code; } ;
struct netsec_priv {int dummy; } ;
struct netsec_desc_ring {struct netsec_desc* desc; scalar_t__ vaddr; } ;
struct netsec_desc {struct sk_buff* skb; } ;
struct netsec_de {int buf_len_info; int attr; } ;

/* Variables and functions */
 size_t DESC_SZ ; 
 int NETSEC_RX_PKT_CO_FIELD ; 
 int NETSEC_RX_PKT_ERR_FIELD ; 
 int NETSEC_RX_PKT_ERR_MASK ; 
 int NETSEC_RX_PKT_ER_FIELD ; 
 int /*<<< orphan*/  memcpy (struct netsec_de*,scalar_t__,size_t) ; 

__attribute__((used)) static struct sk_buff *netsec_get_rx_de(struct netsec_priv *priv,
					struct netsec_desc_ring *dring,
					u16 idx,
					struct netsec_rx_pkt_info *rxpi,
					struct netsec_desc *desc, u16 *len)
{
	struct netsec_de de = {};

	memcpy(&de, dring->vaddr + DESC_SZ * idx, DESC_SZ);

	*len = de.buf_len_info >> 16;

	rxpi->err_flag = (de.attr >> NETSEC_RX_PKT_ER_FIELD) & 1;
	rxpi->rx_cksum_result = (de.attr >> NETSEC_RX_PKT_CO_FIELD) & 3;
	rxpi->err_code = (de.attr >> NETSEC_RX_PKT_ERR_FIELD) &
							NETSEC_RX_PKT_ERR_MASK;
	*desc = dring->desc[idx];
	return desc->skb;
}