#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* head_blk_ctl; } ;
struct wcn36xx {TYPE_3__ dxe_tx_l_ch; int /*<<< orphan*/  dev; TYPE_3__ dxe_tx_h_ch; TYPE_3__ dxe_rx_l_ch; TYPE_3__ dxe_rx_h_ch; int /*<<< orphan*/  mgmt_mem_pool; int /*<<< orphan*/  data_mem_pool; scalar_t__ is_pronto; } ;
struct TYPE_8__ {int desc_phy_addr; TYPE_1__* desc; } ;
struct TYPE_7__ {int phy_next_l; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCN36XX_CCU_DXE_INT_SELECT_PRONTO ; 
 int /*<<< orphan*/  WCN36XX_CCU_DXE_INT_SELECT_RIVA ; 
 int WCN36XX_DXE_CH_DEFAULT_CTL_RX_H ; 
 int WCN36XX_DXE_CH_DEFAULT_CTL_RX_L ; 
 int /*<<< orphan*/  WCN36XX_DXE_CH_DEST_ADDR_RX_H ; 
 int /*<<< orphan*/  WCN36XX_DXE_CH_DEST_ADDR_RX_L ; 
 int /*<<< orphan*/  WCN36XX_DXE_CH_DEST_ADDR_TX_H ; 
 int /*<<< orphan*/  WCN36XX_DXE_CH_DEST_ADDR_TX_L ; 
 int /*<<< orphan*/  WCN36XX_DXE_CH_NEXT_DESC_ADDR_RX_H ; 
 int /*<<< orphan*/  WCN36XX_DXE_CH_NEXT_DESC_ADDR_RX_L ; 
 int /*<<< orphan*/  WCN36XX_DXE_CH_NEXT_DESC_ADDR_TX_H ; 
 int /*<<< orphan*/  WCN36XX_DXE_CH_NEXT_DESC_ADDR_TX_L ; 
 int /*<<< orphan*/  WCN36XX_DXE_CH_SRC_ADDR_RX_H ; 
 int /*<<< orphan*/  WCN36XX_DXE_CH_SRC_ADDR_RX_L ; 
 int WCN36XX_DXE_INT_CH0_MASK ; 
 int WCN36XX_DXE_INT_CH1_MASK ; 
 int WCN36XX_DXE_INT_CH3_MASK ; 
 int WCN36XX_DXE_INT_CH4_MASK ; 
 int /*<<< orphan*/  WCN36XX_DXE_REG_CH_EN ; 
 int /*<<< orphan*/  WCN36XX_DXE_REG_CSR_RESET ; 
 int /*<<< orphan*/  WCN36XX_DXE_REG_CTL_RX_H ; 
 int /*<<< orphan*/  WCN36XX_DXE_REG_CTL_RX_L ; 
 int WCN36XX_DXE_REG_RESET ; 
 int WCN36XX_DXE_WQ_RX_H ; 
 int WCN36XX_DXE_WQ_RX_L ; 
 int WCN36XX_DXE_WQ_TX_H ; 
 int WCN36XX_DXE_WQ_TX_L ; 
 int /*<<< orphan*/  WCN36XX_INT_MASK_CHAN_RX_H ; 
 int /*<<< orphan*/  WCN36XX_INT_MASK_CHAN_RX_L ; 
 int /*<<< orphan*/  WCN36XX_INT_MASK_CHAN_TX_H ; 
 int /*<<< orphan*/  WCN36XX_INT_MASK_CHAN_TX_L ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wcn36xx_ccu_write_register (struct wcn36xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wcn36xx_dxe_ch_alloc_skb (struct wcn36xx*,TYPE_3__*) ; 
 int /*<<< orphan*/  wcn36xx_dxe_deinit_descs (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  wcn36xx_dxe_enable_ch_int (struct wcn36xx*,int /*<<< orphan*/ ) ; 
 int wcn36xx_dxe_init_descs (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  wcn36xx_dxe_init_tx_bd (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dxe_read_register (struct wcn36xx*,int /*<<< orphan*/ ,int*) ; 
 int wcn36xx_dxe_request_irqs (struct wcn36xx*) ; 
 int /*<<< orphan*/  wcn36xx_dxe_write_register (struct wcn36xx*,int /*<<< orphan*/ ,int) ; 

int wcn36xx_dxe_init(struct wcn36xx *wcn)
{
	int reg_data = 0, ret;

	reg_data = WCN36XX_DXE_REG_RESET;
	wcn36xx_dxe_write_register(wcn, WCN36XX_DXE_REG_CSR_RESET, reg_data);

	/* Select channels for rx avail and xfer done interrupts... */
	reg_data = (WCN36XX_DXE_INT_CH3_MASK | WCN36XX_DXE_INT_CH1_MASK) << 16 |
		    WCN36XX_DXE_INT_CH0_MASK | WCN36XX_DXE_INT_CH4_MASK;
	if (wcn->is_pronto)
		wcn36xx_ccu_write_register(wcn, WCN36XX_CCU_DXE_INT_SELECT_PRONTO, reg_data);
	else
		wcn36xx_ccu_write_register(wcn, WCN36XX_CCU_DXE_INT_SELECT_RIVA, reg_data);

	/***************************************/
	/* Init descriptors for TX LOW channel */
	/***************************************/
	ret = wcn36xx_dxe_init_descs(wcn->dev, &wcn->dxe_tx_l_ch);
	if (ret) {
		dev_err(wcn->dev, "Error allocating descriptor\n");
		return ret;
	}
	wcn36xx_dxe_init_tx_bd(&wcn->dxe_tx_l_ch, &wcn->data_mem_pool);

	/* Write channel head to a NEXT register */
	wcn36xx_dxe_write_register(wcn, WCN36XX_DXE_CH_NEXT_DESC_ADDR_TX_L,
		wcn->dxe_tx_l_ch.head_blk_ctl->desc_phy_addr);

	/* Program DMA destination addr for TX LOW */
	wcn36xx_dxe_write_register(wcn,
		WCN36XX_DXE_CH_DEST_ADDR_TX_L,
		WCN36XX_DXE_WQ_TX_L);

	wcn36xx_dxe_read_register(wcn, WCN36XX_DXE_REG_CH_EN, &reg_data);
	wcn36xx_dxe_enable_ch_int(wcn, WCN36XX_INT_MASK_CHAN_TX_L);

	/***************************************/
	/* Init descriptors for TX HIGH channel */
	/***************************************/
	ret = wcn36xx_dxe_init_descs(wcn->dev, &wcn->dxe_tx_h_ch);
	if (ret) {
		dev_err(wcn->dev, "Error allocating descriptor\n");
		goto out_err_txh_ch;
	}

	wcn36xx_dxe_init_tx_bd(&wcn->dxe_tx_h_ch, &wcn->mgmt_mem_pool);

	/* Write channel head to a NEXT register */
	wcn36xx_dxe_write_register(wcn, WCN36XX_DXE_CH_NEXT_DESC_ADDR_TX_H,
		wcn->dxe_tx_h_ch.head_blk_ctl->desc_phy_addr);

	/* Program DMA destination addr for TX HIGH */
	wcn36xx_dxe_write_register(wcn,
		WCN36XX_DXE_CH_DEST_ADDR_TX_H,
		WCN36XX_DXE_WQ_TX_H);

	wcn36xx_dxe_read_register(wcn, WCN36XX_DXE_REG_CH_EN, &reg_data);

	/* Enable channel interrupts */
	wcn36xx_dxe_enable_ch_int(wcn, WCN36XX_INT_MASK_CHAN_TX_H);

	/***************************************/
	/* Init descriptors for RX LOW channel */
	/***************************************/
	ret = wcn36xx_dxe_init_descs(wcn->dev, &wcn->dxe_rx_l_ch);
	if (ret) {
		dev_err(wcn->dev, "Error allocating descriptor\n");
		goto out_err_rxl_ch;
	}


	/* For RX we need to preallocated buffers */
	wcn36xx_dxe_ch_alloc_skb(wcn, &wcn->dxe_rx_l_ch);

	/* Write channel head to a NEXT register */
	wcn36xx_dxe_write_register(wcn, WCN36XX_DXE_CH_NEXT_DESC_ADDR_RX_L,
		wcn->dxe_rx_l_ch.head_blk_ctl->desc_phy_addr);

	/* Write DMA source address */
	wcn36xx_dxe_write_register(wcn,
		WCN36XX_DXE_CH_SRC_ADDR_RX_L,
		WCN36XX_DXE_WQ_RX_L);

	/* Program preallocated destination address */
	wcn36xx_dxe_write_register(wcn,
		WCN36XX_DXE_CH_DEST_ADDR_RX_L,
		wcn->dxe_rx_l_ch.head_blk_ctl->desc->phy_next_l);

	/* Enable default control registers */
	wcn36xx_dxe_write_register(wcn,
		WCN36XX_DXE_REG_CTL_RX_L,
		WCN36XX_DXE_CH_DEFAULT_CTL_RX_L);

	/* Enable channel interrupts */
	wcn36xx_dxe_enable_ch_int(wcn, WCN36XX_INT_MASK_CHAN_RX_L);

	/***************************************/
	/* Init descriptors for RX HIGH channel */
	/***************************************/
	ret = wcn36xx_dxe_init_descs(wcn->dev, &wcn->dxe_rx_h_ch);
	if (ret) {
		dev_err(wcn->dev, "Error allocating descriptor\n");
		goto out_err_rxh_ch;
	}

	/* For RX we need to prealocat buffers */
	wcn36xx_dxe_ch_alloc_skb(wcn, &wcn->dxe_rx_h_ch);

	/* Write chanel head to a NEXT register */
	wcn36xx_dxe_write_register(wcn, WCN36XX_DXE_CH_NEXT_DESC_ADDR_RX_H,
		wcn->dxe_rx_h_ch.head_blk_ctl->desc_phy_addr);

	/* Write DMA source address */
	wcn36xx_dxe_write_register(wcn,
		WCN36XX_DXE_CH_SRC_ADDR_RX_H,
		WCN36XX_DXE_WQ_RX_H);

	/* Program preallocated destination address */
	wcn36xx_dxe_write_register(wcn,
		WCN36XX_DXE_CH_DEST_ADDR_RX_H,
		 wcn->dxe_rx_h_ch.head_blk_ctl->desc->phy_next_l);

	/* Enable default control registers */
	wcn36xx_dxe_write_register(wcn,
		WCN36XX_DXE_REG_CTL_RX_H,
		WCN36XX_DXE_CH_DEFAULT_CTL_RX_H);

	/* Enable channel interrupts */
	wcn36xx_dxe_enable_ch_int(wcn, WCN36XX_INT_MASK_CHAN_RX_H);

	ret = wcn36xx_dxe_request_irqs(wcn);
	if (ret < 0)
		goto out_err_irq;

	return 0;

out_err_irq:
	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_rx_h_ch);
out_err_rxh_ch:
	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_rx_l_ch);
out_err_rxl_ch:
	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_tx_h_ch);
out_err_txh_ch:
	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_tx_l_ch);

	return ret;
}