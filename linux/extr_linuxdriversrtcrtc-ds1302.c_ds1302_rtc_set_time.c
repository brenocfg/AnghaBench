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
typedef  int /*<<< orphan*/  u8 ;
struct spi_device {int dummy; } ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_wday; int tm_year; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int RTC_ADDR_CTRL ; 
 int RTC_CLCK_BURST ; 
 int /*<<< orphan*/  RTC_CLCK_LEN ; 
 int RTC_CMD_WRITE ; 
 int /*<<< orphan*/  RTC_CMD_WRITE_DISABLE ; 
 int /*<<< orphan*/  RTC_CMD_WRITE_ENABLE ; 
 void* bin2bcd (int) ; 
 struct spi_device* dev_get_drvdata (struct device*) ; 
 int spi_write_then_read (struct spi_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds1302_rtc_set_time(struct device *dev, struct rtc_time *time)
{
	struct spi_device	*spi = dev_get_drvdata(dev);
	u8		buf[1 + RTC_CLCK_LEN];
	u8		*bp;
	int		status;

	/* Enable writing */
	bp = buf;
	*bp++ = RTC_ADDR_CTRL << 1 | RTC_CMD_WRITE;
	*bp++ = RTC_CMD_WRITE_ENABLE;

	status = spi_write_then_read(spi, buf, 2,
			NULL, 0);
	if (status)
		return status;

	/* Write registers starting at the first time/date address. */
	bp = buf;
	*bp++ = RTC_CLCK_BURST << 1 | RTC_CMD_WRITE;

	*bp++ = bin2bcd(time->tm_sec);
	*bp++ = bin2bcd(time->tm_min);
	*bp++ = bin2bcd(time->tm_hour);
	*bp++ = bin2bcd(time->tm_mday);
	*bp++ = bin2bcd(time->tm_mon + 1);
	*bp++ = time->tm_wday + 1;
	*bp++ = bin2bcd(time->tm_year % 100);
	*bp++ = RTC_CMD_WRITE_DISABLE;

	/* use write-then-read since dma from stack is nonportable */
	return spi_write_then_read(spi, buf, sizeof(buf),
			NULL, 0);
}