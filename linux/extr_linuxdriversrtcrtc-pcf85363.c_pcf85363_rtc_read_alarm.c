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
struct TYPE_2__ {void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct rtc_wkalrm {int enabled; TYPE_1__ time; } ;
struct pcf85363 {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_INTA_EN ; 
 scalar_t__ DT_MONTH_ALM1 ; 
 scalar_t__ DT_SECOND_ALM1 ; 
 unsigned int INT_A1IE ; 
 void* bcd2bin (unsigned char) ; 
 struct pcf85363* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,scalar_t__,unsigned char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int pcf85363_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct pcf85363 *pcf85363 = dev_get_drvdata(dev);
	unsigned char buf[DT_MONTH_ALM1 - DT_SECOND_ALM1 + 1];
	unsigned int val;
	int ret;

	ret = regmap_bulk_read(pcf85363->regmap, DT_SECOND_ALM1, buf,
			       sizeof(buf));
	if (ret)
		return ret;

	alrm->time.tm_sec = bcd2bin(buf[0]);
	alrm->time.tm_min = bcd2bin(buf[1]);
	alrm->time.tm_hour = bcd2bin(buf[2]);
	alrm->time.tm_mday = bcd2bin(buf[3]);
	alrm->time.tm_mon = bcd2bin(buf[4]) - 1;

	ret = regmap_read(pcf85363->regmap, CTRL_INTA_EN, &val);
	if (ret)
		return ret;

	alrm->enabled =  !!(val & INT_A1IE);

	return 0;
}