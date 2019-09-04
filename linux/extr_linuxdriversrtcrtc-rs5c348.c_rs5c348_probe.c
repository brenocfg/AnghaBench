#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_10__ {struct rs5c348_plat_data* platform_data; } ;
struct spi_device {int max_speed_hz; TYPE_2__ dev; } ;
struct rtc_time {int dummy; } ;
struct rtc_device {int dummy; } ;
struct rs5c348_plat_data {int rtc_24h; struct rtc_device* rtc; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {TYPE_1__ driver; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 int RS5C348_BIT_24H ; 
 int RS5C348_BIT_VDET ; 
 int RS5C348_BIT_XSTP ; 
 int /*<<< orphan*/  RS5C348_CMD_R (int /*<<< orphan*/ ) ; 
 scalar_t__ RS5C348_CMD_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RS5C348_REG_CTL1 ; 
 int /*<<< orphan*/  RS5C348_REG_CTL2 ; 
 int /*<<< orphan*/  RS5C348_REG_SECS ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 struct rs5c348_plat_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct rtc_device* devm_rtc_device_register (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__ rs5c348_driver ; 
 int /*<<< orphan*/  rs5c348_rtc_ops ; 
 int rs5c348_rtc_set_time (TYPE_2__*,struct rtc_time*) ; 
 int /*<<< orphan*/  rtc_time_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 
 int spi_w8r8 (struct spi_device*,int /*<<< orphan*/ ) ; 
 int spi_write_then_read (struct spi_device*,scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs5c348_probe(struct spi_device *spi)
{
	int ret;
	struct rtc_device *rtc;
	struct rs5c348_plat_data *pdata;

	pdata = devm_kzalloc(&spi->dev, sizeof(struct rs5c348_plat_data),
				GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;
	spi->dev.platform_data = pdata;

	/* Check D7 of SECOND register */
	ret = spi_w8r8(spi, RS5C348_CMD_R(RS5C348_REG_SECS));
	if (ret < 0 || (ret & 0x80)) {
		dev_err(&spi->dev, "not found.\n");
		goto kfree_exit;
	}

	dev_info(&spi->dev, "spiclk %u KHz.\n",
		 (spi->max_speed_hz + 500) / 1000);

	/* turn RTC on if it was not on */
	ret = spi_w8r8(spi, RS5C348_CMD_R(RS5C348_REG_CTL2));
	if (ret < 0)
		goto kfree_exit;
	if (ret & (RS5C348_BIT_XSTP | RS5C348_BIT_VDET)) {
		u8 buf[2];
		struct rtc_time tm;
		if (ret & RS5C348_BIT_VDET)
			dev_warn(&spi->dev, "voltage-low detected.\n");
		if (ret & RS5C348_BIT_XSTP)
			dev_warn(&spi->dev, "oscillator-stop detected.\n");
		rtc_time_to_tm(0, &tm);	/* 1970/1/1 */
		ret = rs5c348_rtc_set_time(&spi->dev, &tm);
		if (ret < 0)
			goto kfree_exit;
		buf[0] = RS5C348_CMD_W(RS5C348_REG_CTL2);
		buf[1] = 0;
		ret = spi_write_then_read(spi, buf, sizeof(buf), NULL, 0);
		if (ret < 0)
			goto kfree_exit;
	}

	ret = spi_w8r8(spi, RS5C348_CMD_R(RS5C348_REG_CTL1));
	if (ret < 0)
		goto kfree_exit;
	if (ret & RS5C348_BIT_24H)
		pdata->rtc_24h = 1;

	rtc = devm_rtc_device_register(&spi->dev, rs5c348_driver.driver.name,
				  &rs5c348_rtc_ops, THIS_MODULE);

	if (IS_ERR(rtc)) {
		ret = PTR_ERR(rtc);
		goto kfree_exit;
	}

	pdata->rtc = rtc;

	return 0;
 kfree_exit:
	return ret;
}