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
struct spi_device {int dummy; } ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_wday; int tm_mday; int tm_mon; int tm_year; } ;
struct ds1390 {int* txrx_buf; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DS1390_REG_SECONDS ; 
 int bin2bcd (int) ; 
 struct ds1390* dev_get_drvdata (struct device*) ; 
 int spi_write_then_read (struct spi_device*,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int ds1390_set_time(struct device *dev, struct rtc_time *dt)
{
	struct spi_device *spi = to_spi_device(dev);
	struct ds1390 *chip = dev_get_drvdata(dev);

	/* build the message */
	chip->txrx_buf[0] = DS1390_REG_SECONDS | 0x80;
	chip->txrx_buf[1] = bin2bcd(dt->tm_sec);
	chip->txrx_buf[2] = bin2bcd(dt->tm_min);
	chip->txrx_buf[3] = bin2bcd(dt->tm_hour);
	chip->txrx_buf[4] = bin2bcd(dt->tm_wday);
	chip->txrx_buf[5] = bin2bcd(dt->tm_mday);
	chip->txrx_buf[6] = bin2bcd(dt->tm_mon + 1) |
				((dt->tm_year > 99) ? 0x80 : 0x00);
	chip->txrx_buf[7] = bin2bcd(dt->tm_year % 100);

	/* do the i/o */
	return spi_write_then_read(spi, chip->txrx_buf, 8, NULL, 0);
}