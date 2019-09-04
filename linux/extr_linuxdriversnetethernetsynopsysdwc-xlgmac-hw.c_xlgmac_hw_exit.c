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
struct xlgmac_pdata {scalar_t__ mac_regs; } ;

/* Variables and functions */
 scalar_t__ DMA_MR ; 
 int /*<<< orphan*/  DMA_MR_SWR_LEN ; 
 int /*<<< orphan*/  DMA_MR_SWR_POS ; 
 int EBUSY ; 
 scalar_t__ XLGMAC_GET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int xlgmac_hw_exit(struct xlgmac_pdata *pdata)
{
	unsigned int count = 2000;
	u32 regval;

	/* Issue a software reset */
	regval = readl(pdata->mac_regs + DMA_MR);
	regval = XLGMAC_SET_REG_BITS(regval, DMA_MR_SWR_POS,
				     DMA_MR_SWR_LEN, 1);
	writel(regval, pdata->mac_regs + DMA_MR);
	usleep_range(10, 15);

	/* Poll Until Poll Condition */
	while (--count &&
	       XLGMAC_GET_REG_BITS(readl(pdata->mac_regs + DMA_MR),
				   DMA_MR_SWR_POS, DMA_MR_SWR_LEN))
		usleep_range(500, 600);

	if (!count)
		return -EBUSY;

	return 0;
}