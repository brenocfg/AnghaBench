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
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
struct as3722_rtc {struct as3722* as3722; } ;
struct as3722 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS3722_RTC_SECOND_REG ; 
 int as3722_block_read (struct as3722*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  as3722_reg_to_time (int /*<<< orphan*/ *,struct rtc_time*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct as3722_rtc* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int as3722_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct as3722_rtc *as3722_rtc = dev_get_drvdata(dev);
	struct as3722 *as3722 = as3722_rtc->as3722;
	u8 as_time_array[6];
	int ret;

	ret = as3722_block_read(as3722, AS3722_RTC_SECOND_REG,
			6, as_time_array);
	if (ret < 0) {
		dev_err(dev, "RTC_SECOND reg block read failed %d\n", ret);
		return ret;
	}
	as3722_reg_to_time(as_time_array, tm);
	return 0;
}