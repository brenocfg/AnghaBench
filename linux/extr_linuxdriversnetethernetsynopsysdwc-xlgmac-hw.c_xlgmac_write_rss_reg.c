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
struct xlgmac_pdata {int /*<<< orphan*/  rss_mutex; scalar_t__ mac_regs; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ MAC_RSSAR ; 
 int /*<<< orphan*/  MAC_RSSAR_ADDRT_LEN ; 
 int /*<<< orphan*/  MAC_RSSAR_ADDRT_POS ; 
 int /*<<< orphan*/  MAC_RSSAR_CT_LEN ; 
 int /*<<< orphan*/  MAC_RSSAR_CT_POS ; 
 int /*<<< orphan*/  MAC_RSSAR_OB_LEN ; 
 int /*<<< orphan*/  MAC_RSSAR_OB_POS ; 
 int /*<<< orphan*/  MAC_RSSAR_RSSIA_LEN ; 
 int /*<<< orphan*/  MAC_RSSAR_RSSIA_POS ; 
 scalar_t__ MAC_RSSDR ; 
 int XLGMAC_GET_REG_BITS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XLGMAC_SET_REG_BITS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int xlgmac_write_rss_reg(struct xlgmac_pdata *pdata, unsigned int type,
				unsigned int index, unsigned int val)
{
	unsigned int wait;
	int ret = 0;
	u32 regval;

	mutex_lock(&pdata->rss_mutex);

	regval = XLGMAC_GET_REG_BITS(readl(pdata->mac_regs + MAC_RSSAR),
				     MAC_RSSAR_OB_POS, MAC_RSSAR_OB_LEN);
	if (regval) {
		ret = -EBUSY;
		goto unlock;
	}

	writel(val, pdata->mac_regs + MAC_RSSDR);

	regval = readl(pdata->mac_regs + MAC_RSSAR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RSSAR_RSSIA_POS,
				     MAC_RSSAR_RSSIA_LEN, index);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RSSAR_ADDRT_POS,
				     MAC_RSSAR_ADDRT_LEN, type);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RSSAR_CT_POS,
				     MAC_RSSAR_CT_LEN, 0);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RSSAR_OB_POS,
				     MAC_RSSAR_OB_LEN, 1);
	writel(regval, pdata->mac_regs + MAC_RSSAR);

	wait = 1000;
	while (wait--) {
		regval = XLGMAC_GET_REG_BITS(readl(pdata->mac_regs + MAC_RSSAR),
					     MAC_RSSAR_OB_POS,
					     MAC_RSSAR_OB_LEN);
		if (!regval)
			goto unlock;

		usleep_range(1000, 1500);
	}

	ret = -EBUSY;

unlock:
	mutex_unlock(&pdata->rss_mutex);

	return ret;
}