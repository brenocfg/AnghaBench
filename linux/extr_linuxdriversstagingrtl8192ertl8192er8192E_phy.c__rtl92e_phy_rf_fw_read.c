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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
typedef  enum rf90_radio_path { ____Placeholder_rf90_radio_path } rf90_radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  QPNR ; 
 int /*<<< orphan*/  RF_DATA ; 
 int rtl92e_readl (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92e_writel (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u32 _rtl92e_phy_rf_fw_read(struct net_device *dev,
				  enum rf90_radio_path eRFPath, u32 Offset)
{
	u32		Data = 0;
	u8		time = 0;

	Data |= ((Offset & 0xFF) << 12);
	Data |= ((eRFPath & 0x3) << 20);
	Data |= 0x80000000;
	while (rtl92e_readl(dev, QPNR) & 0x80000000) {
		if (time++ < 100)
			udelay(10);
		else
			break;
	}
	rtl92e_writel(dev, QPNR, Data);
	while (rtl92e_readl(dev, QPNR) & 0x80000000) {
		if (time++ < 100)
			udelay(10);
		else
			return 0;
	}
	return rtl92e_readl(dev, RF_DATA);

}