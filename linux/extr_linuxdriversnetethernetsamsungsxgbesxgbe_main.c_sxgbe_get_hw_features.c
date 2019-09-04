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
struct sxgbe_hw_features {int /*<<< orphan*/  aux_input_count; int /*<<< orphan*/  pps_output_count; int /*<<< orphan*/  tx_dma_channels; int /*<<< orphan*/  rx_dma_channels; int /*<<< orphan*/  tx_mtl_queues; int /*<<< orphan*/  rx_mtl_queues; int /*<<< orphan*/  l3l4_filer_size; int /*<<< orphan*/  hash_tsize; int /*<<< orphan*/  rss_enable; int /*<<< orphan*/  debug_mem; int /*<<< orphan*/  tcpseg_offload; int /*<<< orphan*/  splithead_enable; int /*<<< orphan*/  dcb_enable; void* atstmap_hword; void* txfifo_size; int /*<<< orphan*/  rxfifo_size; int /*<<< orphan*/  eee; int /*<<< orphan*/  sa_vlan_insert; int /*<<< orphan*/  tstamp_srcselect; int /*<<< orphan*/  multi_macaddr; int /*<<< orphan*/  rx_csum_offload; int /*<<< orphan*/  tx_csum_offload; int /*<<< orphan*/  atime_stamp; int /*<<< orphan*/  pmt_magic_frame; int /*<<< orphan*/  pmt_remote_wake_up; } ;
struct sxgbe_priv_data {int /*<<< orphan*/  ioaddr; TYPE_2__* hw; struct sxgbe_hw_features hw_cap; } ;
struct TYPE_4__ {TYPE_1__* mac; } ;
struct TYPE_3__ {int (* get_hw_feature ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SXGBE_HW_FEAT_AUX_SNAPSHOTS (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_DCB (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_DEBUG_MEM_IFACE (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_EEE (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_HASH_TABLE_SIZE (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_IEEE1500_2008 (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_L3L4_FILTER_NUM (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_MACADDR_COUNT (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_PMT_MAGIC_PKT (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_PMT_TEMOTE_WOP (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_PPS_OUTPUTS (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_RSS (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_RX_CSUM_OFFLOAD (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_RX_DMA_CHANNELS (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_RX_FIFO_SIZE (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_RX_MTL_QUEUES (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_SPLIT_HDR (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_SRCADDR_VLAN (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_TSO (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_TSTMAP_SRC (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_TX_CSUM_OFFLOAD (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_TX_DMA_CHANNELS (int) ; 
 void* SXGBE_HW_FEAT_TX_FIFO_SIZE (int) ; 
 int /*<<< orphan*/  SXGBE_HW_FEAT_TX_MTL_QUEUES (int) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ ,int) ; 
 int stub3 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sxgbe_get_hw_features(struct sxgbe_priv_data * const priv)
{
	int rval = 0;
	struct sxgbe_hw_features *features = &priv->hw_cap;

	/* Read First Capability Register CAP[0] */
	rval = priv->hw->mac->get_hw_feature(priv->ioaddr, 0);
	if (rval) {
		features->pmt_remote_wake_up =
			SXGBE_HW_FEAT_PMT_TEMOTE_WOP(rval);
		features->pmt_magic_frame = SXGBE_HW_FEAT_PMT_MAGIC_PKT(rval);
		features->atime_stamp = SXGBE_HW_FEAT_IEEE1500_2008(rval);
		features->tx_csum_offload =
			SXGBE_HW_FEAT_TX_CSUM_OFFLOAD(rval);
		features->rx_csum_offload =
			SXGBE_HW_FEAT_RX_CSUM_OFFLOAD(rval);
		features->multi_macaddr = SXGBE_HW_FEAT_MACADDR_COUNT(rval);
		features->tstamp_srcselect = SXGBE_HW_FEAT_TSTMAP_SRC(rval);
		features->sa_vlan_insert = SXGBE_HW_FEAT_SRCADDR_VLAN(rval);
		features->eee = SXGBE_HW_FEAT_EEE(rval);
	}

	/* Read First Capability Register CAP[1] */
	rval = priv->hw->mac->get_hw_feature(priv->ioaddr, 1);
	if (rval) {
		features->rxfifo_size = SXGBE_HW_FEAT_RX_FIFO_SIZE(rval);
		features->txfifo_size = SXGBE_HW_FEAT_TX_FIFO_SIZE(rval);
		features->atstmap_hword = SXGBE_HW_FEAT_TX_FIFO_SIZE(rval);
		features->dcb_enable = SXGBE_HW_FEAT_DCB(rval);
		features->splithead_enable = SXGBE_HW_FEAT_SPLIT_HDR(rval);
		features->tcpseg_offload = SXGBE_HW_FEAT_TSO(rval);
		features->debug_mem = SXGBE_HW_FEAT_DEBUG_MEM_IFACE(rval);
		features->rss_enable = SXGBE_HW_FEAT_RSS(rval);
		features->hash_tsize = SXGBE_HW_FEAT_HASH_TABLE_SIZE(rval);
		features->l3l4_filer_size = SXGBE_HW_FEAT_L3L4_FILTER_NUM(rval);
	}

	/* Read First Capability Register CAP[2] */
	rval = priv->hw->mac->get_hw_feature(priv->ioaddr, 2);
	if (rval) {
		features->rx_mtl_queues = SXGBE_HW_FEAT_RX_MTL_QUEUES(rval);
		features->tx_mtl_queues = SXGBE_HW_FEAT_TX_MTL_QUEUES(rval);
		features->rx_dma_channels = SXGBE_HW_FEAT_RX_DMA_CHANNELS(rval);
		features->tx_dma_channels = SXGBE_HW_FEAT_TX_DMA_CHANNELS(rval);
		features->pps_output_count = SXGBE_HW_FEAT_PPS_OUTPUTS(rval);
		features->aux_input_count = SXGBE_HW_FEAT_AUX_SNAPSHOTS(rval);
	}

	return rval;
}