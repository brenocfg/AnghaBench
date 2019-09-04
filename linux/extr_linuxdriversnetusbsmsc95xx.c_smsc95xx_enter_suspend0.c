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
struct usbnet {scalar_t__* data; } ;
struct smsc95xx_priv {int wolopts; int /*<<< orphan*/  suspend_flags; } ;

/* Variables and functions */
 int PM_CTL_PHY_RST_ ; 
 int PM_CTL_SUS_MODE_ ; 
 int PM_CTL_SUS_MODE_0 ; 
 int PM_CTL_WUPS_ ; 
 int PM_CTL_WUPS_ED_ ; 
 int PM_CTL_WUPS_WOL_ ; 
 int /*<<< orphan*/  PM_CTRL ; 
 int /*<<< orphan*/  SUSPEND_SUSPEND0 ; 
 int WAKE_PHY ; 
 int smsc95xx_read_reg_nopm (struct usbnet*,int /*<<< orphan*/ ,int*) ; 
 int smsc95xx_write_reg_nopm (struct usbnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smsc95xx_enter_suspend0(struct usbnet *dev)
{
	struct smsc95xx_priv *pdata = (struct smsc95xx_priv *)(dev->data[0]);
	u32 val;
	int ret;

	ret = smsc95xx_read_reg_nopm(dev, PM_CTRL, &val);
	if (ret < 0)
		return ret;

	val &= (~(PM_CTL_SUS_MODE_ | PM_CTL_WUPS_ | PM_CTL_PHY_RST_));
	val |= PM_CTL_SUS_MODE_0;

	ret = smsc95xx_write_reg_nopm(dev, PM_CTRL, val);
	if (ret < 0)
		return ret;

	/* clear wol status */
	val &= ~PM_CTL_WUPS_;
	val |= PM_CTL_WUPS_WOL_;

	/* enable energy detection */
	if (pdata->wolopts & WAKE_PHY)
		val |= PM_CTL_WUPS_ED_;

	ret = smsc95xx_write_reg_nopm(dev, PM_CTRL, val);
	if (ret < 0)
		return ret;

	/* read back PM_CTRL */
	ret = smsc95xx_read_reg_nopm(dev, PM_CTRL, &val);
	if (ret < 0)
		return ret;

	pdata->suspend_flags |= SUSPEND_SUSPEND0;

	return 0;
}