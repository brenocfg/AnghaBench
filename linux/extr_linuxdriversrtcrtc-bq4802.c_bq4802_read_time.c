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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; int tm_wday; } ;
struct device {int dummy; } ;
struct bq4802 {int (* read ) (struct bq4802*,int) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  (* write ) (struct bq4802*,int,int) ;} ;

/* Variables and functions */
 void* bcd2bin (unsigned int) ; 
 struct bq4802* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct bq4802*,int) ; 
 unsigned int stub10 (struct bq4802*,int) ; 
 int /*<<< orphan*/  stub11 (struct bq4802*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct bq4802*,int,int) ; 
 int stub3 (struct bq4802*,int) ; 
 int stub4 (struct bq4802*,int) ; 
 int stub5 (struct bq4802*,int) ; 
 int stub6 (struct bq4802*,int) ; 
 int stub7 (struct bq4802*,int) ; 
 int stub8 (struct bq4802*,int) ; 
 int stub9 (struct bq4802*,int) ; 

__attribute__((used)) static int bq4802_read_time(struct device *dev, struct rtc_time *tm)
{
	struct bq4802 *p = dev_get_drvdata(dev);
	unsigned long flags;
	unsigned int century;
	u8 val;

	spin_lock_irqsave(&p->lock, flags);

	val = p->read(p, 0x0e);
	p->write(p, 0xe, val | 0x08);

	tm->tm_sec = p->read(p, 0x00);
	tm->tm_min = p->read(p, 0x02);
	tm->tm_hour = p->read(p, 0x04);
	tm->tm_mday = p->read(p, 0x06);
	tm->tm_mon = p->read(p, 0x09);
	tm->tm_year = p->read(p, 0x0a);
	tm->tm_wday = p->read(p, 0x08);
	century = p->read(p, 0x0f);

	p->write(p, 0x0e, val);

	spin_unlock_irqrestore(&p->lock, flags);

	tm->tm_sec = bcd2bin(tm->tm_sec);
	tm->tm_min = bcd2bin(tm->tm_min);
	tm->tm_hour = bcd2bin(tm->tm_hour);
	tm->tm_mday = bcd2bin(tm->tm_mday);
	tm->tm_mon = bcd2bin(tm->tm_mon);
	tm->tm_year = bcd2bin(tm->tm_year);
	tm->tm_wday = bcd2bin(tm->tm_wday);
	century = bcd2bin(century);

	tm->tm_year += (century * 100);
	tm->tm_year -= 1900;

	tm->tm_mon--;

	return 0;
}