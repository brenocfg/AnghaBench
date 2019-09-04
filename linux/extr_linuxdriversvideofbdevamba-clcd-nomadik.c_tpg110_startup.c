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

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grestb ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int tpg110_read_reg (int) ; 
 int /*<<< orphan*/  tpg110_write_reg (int,int) ; 

__attribute__((used)) static void tpg110_startup(struct device *dev)
{
	u8 val;

	dev_info(dev, "TPG110 display enable\n");
	/* De-assert the reset signal */
	gpiod_set_value_cansleep(grestb, 0);
	mdelay(1);
	dev_info(dev, "de-asserted GRESTB\n");

	/* Test display communication */
	tpg110_write_reg(0x00, 0x55);
	val = tpg110_read_reg(0x00);
	if (val == 0x55)
		dev_info(dev, "passed communication test\n");
	val = tpg110_read_reg(0x01);
	dev_info(dev, "TPG110 chip ID: %d version: %d\n",
		val>>4, val&0x0f);

	/* Show display resolution */
	val = tpg110_read_reg(0x02);
	val &= 7;
	switch (val) {
	case 0x0:
		dev_info(dev, "IN 400x240 RGB -> OUT 800x480 RGB (dual scan)");
		break;
	case 0x1:
		dev_info(dev, "IN 480x272 RGB -> OUT 800x480 RGB (dual scan)");
		break;
	case 0x4:
		dev_info(dev, "480x640 RGB");
		break;
	case 0x5:
		dev_info(dev, "480x272 RGB");
		break;
	case 0x6:
		dev_info(dev, "640x480 RGB");
		break;
	case 0x7:
		dev_info(dev, "800x480 RGB");
		break;
	default:
		dev_info(dev, "ILLEGAL RESOLUTION");
		break;
	}

	val = tpg110_read_reg(0x03);
	dev_info(dev, "resolution is controlled by %s\n",
		(val & BIT(7)) ? "software" : "hardware");
}