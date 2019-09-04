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
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct dpaa2_eth_priv {TYPE_1__* net_dev; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int DPAA2_FAS_L3CV ; 
 int DPAA2_FAS_L4CV ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 

__attribute__((used)) static void validate_rx_csum(struct dpaa2_eth_priv *priv,
			     u32 fd_status,
			     struct sk_buff *skb)
{
	skb_checksum_none_assert(skb);

	/* HW checksum validation is disabled, nothing to do here */
	if (!(priv->net_dev->features & NETIF_F_RXCSUM))
		return;

	/* Read checksum validation bits */
	if (!((fd_status & DPAA2_FAS_L3CV) &&
	      (fd_status & DPAA2_FAS_L4CV)))
		return;

	/* Inform the stack there's no need to compute L3/L4 csum anymore */
	skb->ip_summed = CHECKSUM_UNNECESSARY;
}