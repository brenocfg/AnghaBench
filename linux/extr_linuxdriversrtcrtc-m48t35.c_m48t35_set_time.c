#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
struct rtc_time {int tm_year; int tm_mon; unsigned char tm_mday; unsigned char tm_hour; unsigned char tm_min; unsigned char tm_sec; } ;
struct m48t35_priv {int /*<<< orphan*/  lock; TYPE_1__* reg; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  control; int /*<<< orphan*/  sec; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  date; int /*<<< orphan*/  month; int /*<<< orphan*/  year; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned char M48T35_RTC_SET ; 
 void* bin2bcd (unsigned int) ; 
 struct m48t35_priv* dev_get_drvdata (struct device*) ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int m48t35_set_time(struct device *dev, struct rtc_time *tm)
{
	struct m48t35_priv *priv = dev_get_drvdata(dev);
	unsigned char mon, day, hrs, min, sec;
	unsigned int yrs;
	u8 control;

	yrs = tm->tm_year + 1900;
	mon = tm->tm_mon + 1;   /* tm_mon starts at zero */
	day = tm->tm_mday;
	hrs = tm->tm_hour;
	min = tm->tm_min;
	sec = tm->tm_sec;

	if (yrs < 1970)
		return -EINVAL;

	yrs -= 1970;
	if (yrs > 255)    /* They are unsigned */
		return -EINVAL;

	if (yrs > 169)
		return -EINVAL;

	if (yrs >= 100)
		yrs -= 100;

	sec = bin2bcd(sec);
	min = bin2bcd(min);
	hrs = bin2bcd(hrs);
	day = bin2bcd(day);
	mon = bin2bcd(mon);
	yrs = bin2bcd(yrs);

	spin_lock_irq(&priv->lock);
	control = readb(&priv->reg->control);
	writeb(control | M48T35_RTC_SET, &priv->reg->control);
	writeb(yrs, &priv->reg->year);
	writeb(mon, &priv->reg->month);
	writeb(day, &priv->reg->date);
	writeb(hrs, &priv->reg->hour);
	writeb(min, &priv->reg->min);
	writeb(sec, &priv->reg->sec);
	writeb(control, &priv->reg->control);
	spin_unlock_irq(&priv->lock);
	return 0;
}