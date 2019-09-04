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
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; } ;
struct rtc_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int /*<<< orphan*/  MAX6916_CONTROL_REG ; 
 int /*<<< orphan*/  MAX6916_SECONDS_REG ; 
 int /*<<< orphan*/  MAX6916_STATUS_REG ; 
 int PTR_ERR (struct rtc_device*) ; 
 int /*<<< orphan*/  SPI_MODE_3 ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned char) ; 
 struct rtc_device* devm_rtc_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int max6916_read_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  max6916_rtc_ops ; 
 int /*<<< orphan*/  max6916_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct rtc_device*) ; 
 int /*<<< orphan*/  spi_setup (struct spi_device*) ; 

__attribute__((used)) static int max6916_probe(struct spi_device *spi)
{
	struct rtc_device *rtc;
	unsigned char data;
	int res;

	/* spi setup with max6916 in mode 3 and bits per word as 8 */
	spi->mode = SPI_MODE_3;
	spi->bits_per_word = 8;
	spi_setup(spi);

	/* RTC Settings */
	res = max6916_read_reg(&spi->dev, MAX6916_SECONDS_REG, &data);
	if (res)
		return res;

	/* Disable the write protect of rtc */
	max6916_read_reg(&spi->dev, MAX6916_CONTROL_REG, &data);
	data = data & ~(1 << 7);
	max6916_write_reg(&spi->dev, MAX6916_CONTROL_REG, data);

	/*Enable oscillator,disable oscillator stop flag, glitch filter*/
	max6916_read_reg(&spi->dev, MAX6916_STATUS_REG, &data);
	data = data & 0x1B;
	max6916_write_reg(&spi->dev, MAX6916_STATUS_REG, data);

	/* display the settings */
	max6916_read_reg(&spi->dev, MAX6916_CONTROL_REG, &data);
	dev_info(&spi->dev, "MAX6916 RTC CTRL Reg = 0x%02x\n", data);

	max6916_read_reg(&spi->dev, MAX6916_STATUS_REG, &data);
	dev_info(&spi->dev, "MAX6916 RTC Status Reg = 0x%02x\n", data);

	rtc = devm_rtc_device_register(&spi->dev, "max6916",
				       &max6916_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc))
		return PTR_ERR(rtc);

	spi_set_drvdata(spi, rtc);

	return 0;
}