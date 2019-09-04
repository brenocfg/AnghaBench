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
typedef  int u32 ;
struct xlgmac_pdata {int /*<<< orphan*/  channel_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_TCR ; 
 int /*<<< orphan*/  DMA_CH_TCR_PBL_LEN ; 
 int /*<<< orphan*/  DMA_CH_TCR_PBL_POS ; 
 int /*<<< orphan*/  XLGMAC_DMA_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XLGMAC_GET_REG_BITS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlgmac_get_tx_pbl_val(struct xlgmac_pdata *pdata)
{
	u32 regval;

	regval = readl(XLGMAC_DMA_REG(pdata->channel_head, DMA_CH_TCR));
	regval = XLGMAC_GET_REG_BITS(regval, DMA_CH_TCR_PBL_POS,
				     DMA_CH_TCR_PBL_LEN);
	return regval;
}