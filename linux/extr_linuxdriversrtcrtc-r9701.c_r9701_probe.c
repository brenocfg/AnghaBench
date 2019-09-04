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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct rtc_time {int tm_mday; int tm_year; scalar_t__ tm_mon; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; } ;
struct rtc_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 unsigned char R100CNT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct rtc_device* devm_rtc_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ r9701_get_datetime (int /*<<< orphan*/ *,struct rtc_time*) ; 
 int /*<<< orphan*/  r9701_rtc_ops ; 
 scalar_t__ r9701_set_datetime (int /*<<< orphan*/ *,struct rtc_time*) ; 
 int read_regs (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct rtc_device*) ; 

__attribute__((used)) static int r9701_probe(struct spi_device *spi)
{
	struct rtc_device *rtc;
	struct rtc_time dt;
	unsigned char tmp;
	int res;

	tmp = R100CNT;
	res = read_regs(&spi->dev, &tmp, 1);
	if (res || tmp != 0x20) {
		dev_err(&spi->dev, "cannot read RTC register\n");
		return -ENODEV;
	}

	/*
	 * The device seems to be present. Now check if the registers
	 * contain invalid values. If so, try to write a default date:
	 * 2000/1/1 00:00:00
	 */
	if (r9701_get_datetime(&spi->dev, &dt)) {
		dev_info(&spi->dev, "trying to repair invalid date/time\n");
		dt.tm_sec  = 0;
		dt.tm_min  = 0;
		dt.tm_hour = 0;
		dt.tm_mday = 1;
		dt.tm_mon  = 0;
		dt.tm_year = 100;

		if (r9701_set_datetime(&spi->dev, &dt) ||
				r9701_get_datetime(&spi->dev, &dt)) {
			dev_err(&spi->dev, "cannot repair RTC register\n");
			return -ENODEV;
		}
	}

	rtc = devm_rtc_device_register(&spi->dev, "r9701",
				&r9701_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc))
		return PTR_ERR(rtc);

	spi_set_drvdata(spi, rtc);

	return 0;
}