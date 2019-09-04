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
struct rtc_time {int tm_year; int tm_mday; int tm_hour; int tm_min; int tm_sec; int tm_wday; int /*<<< orphan*/  tm_mon; } ;
struct m48t59_private {int /*<<< orphan*/  lock; } ;
struct m48t59_plat_data {scalar_t__ type; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ M48T59RTC_TYPE_M48T59 ; 
 int /*<<< orphan*/  M48T59_CLEAR_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M48T59_CNTL ; 
 int /*<<< orphan*/  M48T59_CNTL_WRITE ; 
 int /*<<< orphan*/  M48T59_HOUR ; 
 int /*<<< orphan*/  M48T59_MDAY ; 
 int /*<<< orphan*/  M48T59_MIN ; 
 int /*<<< orphan*/  M48T59_MONTH ; 
 int /*<<< orphan*/  M48T59_SEC ; 
 int /*<<< orphan*/  M48T59_SET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M48T59_WDAY ; 
 int M48T59_WDAY_CB ; 
 int M48T59_WDAY_CEB ; 
 int /*<<< orphan*/  M48T59_WRITE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M48T59_YEAR ; 
 int bin2bcd (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int /*<<< orphan*/ ,int,int,int,int) ; 
 struct m48t59_private* dev_get_drvdata (struct device*) ; 
 struct m48t59_plat_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int m48t59_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct m48t59_plat_data *pdata = dev_get_platdata(dev);
	struct m48t59_private *m48t59 = dev_get_drvdata(dev);
	unsigned long flags;
	u8 val = 0;
	int year = tm->tm_year;

#ifdef CONFIG_SPARC
	/* Sun SPARC machines count years since 1968 */
	year -= 68;
#endif

	dev_dbg(dev, "RTC set time %04d-%02d-%02d %02d/%02d/%02d\n",
		year + 1900, tm->tm_mon, tm->tm_mday,
		tm->tm_hour, tm->tm_min, tm->tm_sec);

	if (year < 0)
		return -EINVAL;

	spin_lock_irqsave(&m48t59->lock, flags);
	/* Issue the WRITE command */
	M48T59_SET_BITS(M48T59_CNTL_WRITE, M48T59_CNTL);

	M48T59_WRITE((bin2bcd(tm->tm_sec) & 0x7F), M48T59_SEC);
	M48T59_WRITE((bin2bcd(tm->tm_min) & 0x7F), M48T59_MIN);
	M48T59_WRITE((bin2bcd(tm->tm_hour) & 0x3F), M48T59_HOUR);
	M48T59_WRITE((bin2bcd(tm->tm_mday) & 0x3F), M48T59_MDAY);
	/* tm_mon is 0-11 */
	M48T59_WRITE((bin2bcd(tm->tm_mon + 1) & 0x1F), M48T59_MONTH);
	M48T59_WRITE(bin2bcd(year % 100), M48T59_YEAR);

	if (pdata->type == M48T59RTC_TYPE_M48T59 && (year / 100))
		val = (M48T59_WDAY_CEB | M48T59_WDAY_CB);
	val |= (bin2bcd(tm->tm_wday) & 0x07);
	M48T59_WRITE(val, M48T59_WDAY);

	/* Clear the WRITE bit */
	M48T59_CLEAR_BITS(M48T59_CNTL_WRITE, M48T59_CNTL);
	spin_unlock_irqrestore(&m48t59->lock, flags);
	return 0;
}