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
struct wcn36xx {int /*<<< orphan*/  dxe_rx_h_ch; int /*<<< orphan*/  dxe_rx_l_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCN36XX_DXE_CH_STATUS_REG_ADDR_RX_H ; 
 int /*<<< orphan*/  WCN36XX_DXE_CH_STATUS_REG_ADDR_RX_L ; 
 int /*<<< orphan*/  WCN36XX_DXE_CTRL_RX_H ; 
 int /*<<< orphan*/  WCN36XX_DXE_CTRL_RX_L ; 
 int WCN36XX_DXE_INT_CH1_MASK ; 
 int WCN36XX_DXE_INT_CH3_MASK ; 
 int /*<<< orphan*/  WCN36XX_DXE_INT_SRC_RAW_REG ; 
 int /*<<< orphan*/  WCN36XX_INT_MASK_CHAN_RX_H ; 
 int /*<<< orphan*/  WCN36XX_INT_MASK_CHAN_RX_L ; 
 int /*<<< orphan*/  wcn36xx_dxe_read_register (struct wcn36xx*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wcn36xx_rx_handle_packets (struct wcn36xx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_warn (char*) ; 

void wcn36xx_dxe_rx_frame(struct wcn36xx *wcn)
{
	int int_src;

	wcn36xx_dxe_read_register(wcn, WCN36XX_DXE_INT_SRC_RAW_REG, &int_src);

	/* RX_LOW_PRI */
	if (int_src & WCN36XX_DXE_INT_CH1_MASK)
		wcn36xx_rx_handle_packets(wcn, &wcn->dxe_rx_l_ch,
					  WCN36XX_DXE_CTRL_RX_L,
					  WCN36XX_DXE_INT_CH1_MASK,
					  WCN36XX_INT_MASK_CHAN_RX_L,
					  WCN36XX_DXE_CH_STATUS_REG_ADDR_RX_L);

	/* RX_HIGH_PRI */
	if (int_src & WCN36XX_DXE_INT_CH3_MASK)
		wcn36xx_rx_handle_packets(wcn, &wcn->dxe_rx_h_ch,
					  WCN36XX_DXE_CTRL_RX_H,
					  WCN36XX_DXE_INT_CH3_MASK,
					  WCN36XX_INT_MASK_CHAN_RX_H,
					  WCN36XX_DXE_CH_STATUS_REG_ADDR_RX_H);

	if (!int_src)
		wcn36xx_warn("No DXE interrupt pending\n");
}