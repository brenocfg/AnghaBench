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
struct xlgmac_pdata {int tx_pause; int rx_pause; int /*<<< orphan*/  drv_ver; int /*<<< orphan*/  drv_name; int /*<<< orphan*/  sysclk_rate; int /*<<< orphan*/  phy_speed; int /*<<< orphan*/  rx_threshold; int /*<<< orphan*/  tx_threshold; void* rx_pbl; void* tx_pbl; int /*<<< orphan*/  pblx8; int /*<<< orphan*/  rx_sf_mode; int /*<<< orphan*/  tx_sf_mode; int /*<<< orphan*/  tx_osp_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_OSP_ENABLE ; 
 void* DMA_PBL_32 ; 
 int /*<<< orphan*/  DMA_PBL_X8_ENABLE ; 
 int /*<<< orphan*/  MTL_RSF_DISABLE ; 
 int /*<<< orphan*/  MTL_RX_THRESHOLD_128 ; 
 int /*<<< orphan*/  MTL_TSF_ENABLE ; 
 int /*<<< orphan*/  MTL_TX_THRESHOLD_128 ; 
 int /*<<< orphan*/  SPEED_25000 ; 
 int /*<<< orphan*/  XLGMAC_DRV_NAME ; 
 int /*<<< orphan*/  XLGMAC_DRV_VERSION ; 
 int /*<<< orphan*/  XLGMAC_SYSCLOCK ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xlgmac_default_config(struct xlgmac_pdata *pdata)
{
	pdata->tx_osp_mode = DMA_OSP_ENABLE;
	pdata->tx_sf_mode = MTL_TSF_ENABLE;
	pdata->rx_sf_mode = MTL_RSF_DISABLE;
	pdata->pblx8 = DMA_PBL_X8_ENABLE;
	pdata->tx_pbl = DMA_PBL_32;
	pdata->rx_pbl = DMA_PBL_32;
	pdata->tx_threshold = MTL_TX_THRESHOLD_128;
	pdata->rx_threshold = MTL_RX_THRESHOLD_128;
	pdata->tx_pause = 1;
	pdata->rx_pause = 1;
	pdata->phy_speed = SPEED_25000;
	pdata->sysclk_rate = XLGMAC_SYSCLOCK;

	strlcpy(pdata->drv_name, XLGMAC_DRV_NAME, sizeof(pdata->drv_name));
	strlcpy(pdata->drv_ver, XLGMAC_DRV_VERSION, sizeof(pdata->drv_ver));
}