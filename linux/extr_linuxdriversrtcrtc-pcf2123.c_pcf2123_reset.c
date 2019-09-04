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
typedef  int u8 ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  rxbuf ;

/* Variables and functions */
 int CTRL1_CLEAR ; 
 int CTRL1_STOP ; 
 int CTRL1_SW_RESET ; 
 int ENODEV ; 
 int /*<<< orphan*/  PCF2123_REG_CTRL1 ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int pcf2123_read (struct device*,int /*<<< orphan*/ ,int*,int) ; 
 int pcf2123_write_reg (struct device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pcf2123_reset(struct device *dev)
{
	int ret;
	u8  rxbuf[2];

	ret = pcf2123_write_reg(dev, PCF2123_REG_CTRL1, CTRL1_SW_RESET);
	if (ret < 0)
		return ret;

	/* Stop the counter */
	dev_dbg(dev, "stopping RTC\n");
	ret = pcf2123_write_reg(dev, PCF2123_REG_CTRL1, CTRL1_STOP);
	if (ret < 0)
		return ret;

	/* See if the counter was actually stopped */
	dev_dbg(dev, "checking for presence of RTC\n");
	ret = pcf2123_read(dev, PCF2123_REG_CTRL1, rxbuf, sizeof(rxbuf));
	if (ret < 0)
		return ret;

	dev_dbg(dev, "received data from RTC (0x%02X 0x%02X)\n",
		rxbuf[0], rxbuf[1]);
	if (!(rxbuf[0] & CTRL1_STOP))
		return -ENODEV;

	/* Start the counter */
	ret = pcf2123_write_reg(dev, PCF2123_REG_CTRL1, CTRL1_CLEAR);
	if (ret < 0)
		return ret;

	return 0;
}