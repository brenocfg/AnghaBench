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
typedef  int /*<<< orphan*/  u32 ;
struct xlgmac_pdata {unsigned int rx_q_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTL_Q_RQFCR ; 
 int /*<<< orphan*/  MTL_Q_RQFCR_RFA_LEN ; 
 int /*<<< orphan*/  MTL_Q_RQFCR_RFA_POS ; 
 int /*<<< orphan*/  MTL_Q_RQFCR_RFD_LEN ; 
 int /*<<< orphan*/  MTL_Q_RQFCR_RFD_POS ; 
 int /*<<< orphan*/  XLGMAC_MTL_REG (struct xlgmac_pdata*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xlgmac_config_flow_control_threshold(struct xlgmac_pdata *pdata)
{
	unsigned int i;
	u32 regval;

	for (i = 0; i < pdata->rx_q_count; i++) {
		regval = readl(XLGMAC_MTL_REG(pdata, i, MTL_Q_RQFCR));
		/* Activate flow control when less than 4k left in fifo */
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_RQFCR_RFA_POS,
					     MTL_Q_RQFCR_RFA_LEN, 2);
		/* De-activate flow control when more than 6k left in fifo */
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_RQFCR_RFD_POS,
					     MTL_Q_RQFCR_RFD_LEN, 4);
		writel(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_RQFCR));
	}
}