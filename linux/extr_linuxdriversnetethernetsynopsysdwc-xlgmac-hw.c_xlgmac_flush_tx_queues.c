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
typedef  scalar_t__ u32 ;
struct xlgmac_pdata {unsigned int tx_q_count; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MTL_Q_TQOMR ; 
 int /*<<< orphan*/  MTL_Q_TQOMR_FTQ_LEN ; 
 int /*<<< orphan*/  MTL_Q_TQOMR_FTQ_POS ; 
 scalar_t__ XLGMAC_GET_REG_BITS (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLGMAC_MTL_REG (struct xlgmac_pdata*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ XLGMAC_SET_REG_BITS (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlgmac_flush_tx_queues(struct xlgmac_pdata *pdata)
{
	unsigned int i, count;
	u32 regval;

	for (i = 0; i < pdata->tx_q_count; i++) {
		regval = readl(XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_TQOMR_FTQ_POS,
					     MTL_Q_TQOMR_FTQ_LEN, 1);
		writel(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
	}

	/* Poll Until Poll Condition */
	for (i = 0; i < pdata->tx_q_count; i++) {
		count = 2000;
		regval = readl(XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
		regval = XLGMAC_GET_REG_BITS(regval, MTL_Q_TQOMR_FTQ_POS,
					     MTL_Q_TQOMR_FTQ_LEN);
		while (--count && regval)
			usleep_range(500, 600);

		if (!count)
			return -EBUSY;
	}

	return 0;
}