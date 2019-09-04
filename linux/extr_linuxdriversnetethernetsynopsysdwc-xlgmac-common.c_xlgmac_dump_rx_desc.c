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
struct xlgmac_ring {int dummy; } ;
struct xlgmac_pdata {int /*<<< orphan*/  netdev; } ;
struct xlgmac_dma_desc {int /*<<< orphan*/  desc3; int /*<<< orphan*/  desc2; int /*<<< orphan*/  desc1; int /*<<< orphan*/  desc0; } ;
struct xlgmac_desc_data {int /*<<< orphan*/  dma_desc_addr; struct xlgmac_dma_desc* dma_desc; } ;

/* Variables and functions */
 struct xlgmac_desc_data* XLGMAC_GET_DESC_DATA (struct xlgmac_ring*,unsigned int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 

void xlgmac_dump_rx_desc(struct xlgmac_pdata *pdata,
			 struct xlgmac_ring *ring,
			 unsigned int idx)
{
	struct xlgmac_desc_data *desc_data;
	struct xlgmac_dma_desc *dma_desc;

	desc_data = XLGMAC_GET_DESC_DATA(ring, idx);
	dma_desc = desc_data->dma_desc;

	netdev_dbg(pdata->netdev, "RX: dma_desc=%p, dma_desc_addr=%pad\n",
		   desc_data->dma_desc, &desc_data->dma_desc_addr);
	netdev_dbg(pdata->netdev,
		   "RX_NORMAL_DESC[%d RX BY DEVICE] = %08x:%08x:%08x:%08x\n",
		   idx,
		   le32_to_cpu(dma_desc->desc0),
		   le32_to_cpu(dma_desc->desc1),
		   le32_to_cpu(dma_desc->desc2),
		   le32_to_cpu(dma_desc->desc3));
}