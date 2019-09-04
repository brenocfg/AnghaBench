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
struct TYPE_2__ {int /*<<< orphan*/  rss; } ;
struct xlgmac_pdata {scalar_t__ mac_regs; TYPE_1__ hw_feat; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ MAC_RSSCR ; 
 int /*<<< orphan*/  MAC_RSSCR_RSSE_LEN ; 
 int /*<<< orphan*/  MAC_RSSCR_RSSE_POS ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int xlgmac_disable_rss(struct xlgmac_pdata *pdata)
{
	u32 regval;

	if (!pdata->hw_feat.rss)
		return -EOPNOTSUPP;

	regval = readl(pdata->mac_regs + MAC_RSSCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RSSCR_RSSE_POS,
				     MAC_RSSCR_RSSE_LEN, 0);
	writel(regval, pdata->mac_regs + MAC_RSSCR);

	return 0;
}