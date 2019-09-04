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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned int tc_cnt; } ;
struct xlgmac_pdata {scalar_t__ mac_regs; TYPE_1__ hw_feat; } ;

/* Variables and functions */
 int MTL_ETSALG_WRR ; 
 scalar_t__ MTL_OMR ; 
 int /*<<< orphan*/  MTL_OMR_ETSALG_LEN ; 
 int /*<<< orphan*/  MTL_OMR_ETSALG_POS ; 
 int /*<<< orphan*/  MTL_OMR_RAA_LEN ; 
 int /*<<< orphan*/  MTL_OMR_RAA_POS ; 
 int MTL_RAA_SP ; 
 int /*<<< orphan*/  MTL_TC_ETSCR ; 
 int /*<<< orphan*/  MTL_TC_ETSCR_TSA_LEN ; 
 int /*<<< orphan*/  MTL_TC_ETSCR_TSA_POS ; 
 int /*<<< orphan*/  MTL_TC_QWR ; 
 int /*<<< orphan*/  MTL_TC_QWR_QW_LEN ; 
 int /*<<< orphan*/  MTL_TC_QWR_QW_POS ; 
 int MTL_TSA_ETS ; 
 scalar_t__ XLGMAC_MTL_REG (struct xlgmac_pdata*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void xlgmac_config_mtl_mode(struct xlgmac_pdata *pdata)
{
	unsigned int i;
	u32 regval;

	/* Set Tx to weighted round robin scheduling algorithm */
	regval = readl(pdata->mac_regs + MTL_OMR);
	regval = XLGMAC_SET_REG_BITS(regval, MTL_OMR_ETSALG_POS,
				     MTL_OMR_ETSALG_LEN, MTL_ETSALG_WRR);
	writel(regval, pdata->mac_regs + MTL_OMR);

	/* Set Tx traffic classes to use WRR algorithm with equal weights */
	for (i = 0; i < pdata->hw_feat.tc_cnt; i++) {
		regval = readl(XLGMAC_MTL_REG(pdata, i, MTL_TC_ETSCR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_TC_ETSCR_TSA_POS,
					     MTL_TC_ETSCR_TSA_LEN, MTL_TSA_ETS);
		writel(regval, XLGMAC_MTL_REG(pdata, i, MTL_TC_ETSCR));

		regval = readl(XLGMAC_MTL_REG(pdata, i, MTL_TC_QWR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_TC_QWR_QW_POS,
					     MTL_TC_QWR_QW_LEN, 1);
		writel(regval, XLGMAC_MTL_REG(pdata, i, MTL_TC_QWR));
	}

	/* Set Rx to strict priority algorithm */
	regval = readl(pdata->mac_regs + MTL_OMR);
	regval = XLGMAC_SET_REG_BITS(regval, MTL_OMR_RAA_POS,
				     MTL_OMR_RAA_LEN, MTL_RAA_SP);
	writel(regval, pdata->mac_regs + MTL_OMR);
}