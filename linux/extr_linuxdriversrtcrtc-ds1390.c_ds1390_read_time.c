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
struct rtc_time {void* tm_year; void* tm_mon; void* tm_mday; void* tm_wday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct ds1390 {int* txrx_buf; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DS1390_REG_SECONDS ; 
 void* bcd2bin (int) ; 
 struct ds1390* dev_get_drvdata (struct device*) ; 
 int spi_write_then_read (struct spi_device*,int*,int,int*,int) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int ds1390_read_time(struct device *dev, struct rtc_time *dt)
{
	struct spi_device *spi = to_spi_device(dev);
	struct ds1390 *chip = dev_get_drvdata(dev);
	int status;

	/* build the message */
	chip->txrx_buf[0] = DS1390_REG_SECONDS;

	/* do the i/o */
	status = spi_write_then_read(spi, chip->txrx_buf, 1, chip->txrx_buf, 8);
	if (status != 0)
		return status;

	/* The chip sends data in this order:
	 * Seconds, Minutes, Hours, Day, Date, Month / Century, Year */
	dt->tm_sec	= bcd2bin(chip->txrx_buf[0]);
	dt->tm_min	= bcd2bin(chip->txrx_buf[1]);
	dt->tm_hour	= bcd2bin(chip->txrx_buf[2]);
	dt->tm_wday	= bcd2bin(chip->txrx_buf[3]);
	dt->tm_mday	= bcd2bin(chip->txrx_buf[4]);
	/* mask off century bit */
	dt->tm_mon	= bcd2bin(chip->txrx_buf[5] & 0x7f) - 1;
	/* adjust for century bit */
	dt->tm_year = bcd2bin(chip->txrx_buf[6]) + ((chip->txrx_buf[5] & 0x80) ? 100 : 0);

	return 0;
}