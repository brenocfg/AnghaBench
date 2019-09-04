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
struct rtc_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 int /*<<< orphan*/  RX4581_REG_SC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct rtc_device* devm_rtc_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rx4581_get_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  rx4581_rtc_ops ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct rtc_device*) ; 

__attribute__((used)) static int rx4581_probe(struct spi_device *spi)
{
	struct rtc_device *rtc;
	unsigned char tmp;
	int res;

	res = rx4581_get_reg(&spi->dev, RX4581_REG_SC, &tmp);
	if (res != 0)
		return res;

	rtc = devm_rtc_device_register(&spi->dev, "rx4581",
				&rx4581_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc))
		return PTR_ERR(rtc);

	spi_set_drvdata(spi, rtc);
	return 0;
}