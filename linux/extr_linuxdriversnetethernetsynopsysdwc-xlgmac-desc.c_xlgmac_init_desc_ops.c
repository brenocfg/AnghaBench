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
struct xlgmac_desc_ops {int /*<<< orphan*/  rx_desc_init; int /*<<< orphan*/  tx_desc_init; int /*<<< orphan*/  unmap_desc_data; int /*<<< orphan*/  map_rx_buffer; int /*<<< orphan*/  map_tx_skb; int /*<<< orphan*/  free_channels_and_rings; int /*<<< orphan*/  alloc_channles_and_rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  xlgmac_alloc_channels_and_rings ; 
 int /*<<< orphan*/  xlgmac_free_channels_and_rings ; 
 int /*<<< orphan*/  xlgmac_map_rx_buffer ; 
 int /*<<< orphan*/  xlgmac_map_tx_skb ; 
 int /*<<< orphan*/  xlgmac_rx_desc_init ; 
 int /*<<< orphan*/  xlgmac_tx_desc_init ; 
 int /*<<< orphan*/  xlgmac_unmap_desc_data ; 

void xlgmac_init_desc_ops(struct xlgmac_desc_ops *desc_ops)
{
	desc_ops->alloc_channles_and_rings = xlgmac_alloc_channels_and_rings;
	desc_ops->free_channels_and_rings = xlgmac_free_channels_and_rings;
	desc_ops->map_tx_skb = xlgmac_map_tx_skb;
	desc_ops->map_rx_buffer = xlgmac_map_rx_buffer;
	desc_ops->unmap_desc_data = xlgmac_unmap_desc_data;
	desc_ops->tx_desc_init = xlgmac_tx_desc_init;
	desc_ops->rx_desc_init = xlgmac_rx_desc_init;
}