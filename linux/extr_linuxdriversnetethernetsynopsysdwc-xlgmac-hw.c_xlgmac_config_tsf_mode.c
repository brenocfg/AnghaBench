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
struct xlgmac_pdata {unsigned int tx_q_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTL_Q_TQOMR ; 
 int /*<<< orphan*/  MTL_Q_TQOMR_TSF_LEN ; 
 int /*<<< orphan*/  MTL_Q_TQOMR_TSF_POS ; 
 int /*<<< orphan*/  XLGMAC_MTL_REG (struct xlgmac_pdata*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlgmac_config_tsf_mode(struct xlgmac_pdata *pdata,
				  unsigned int val)
{
	unsigned int i;
	u32 regval;

	for (i = 0; i < pdata->tx_q_count; i++) {
		regval = readl(XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_TQOMR_TSF_POS,
					     MTL_Q_TQOMR_TSF_LEN, val);
		writel(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
	}

	return 0;
}