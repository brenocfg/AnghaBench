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
struct rtc_time {int dummy; } ;
struct pl031_local {scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTC_DR ; 
 scalar_t__ RTC_YDR ; 
 struct pl031_local* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pl031_stv2_time_to_tm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtc_time*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int pl031_stv2_read_time(struct device *dev, struct rtc_time *tm)
{
	struct pl031_local *ldata = dev_get_drvdata(dev);

	pl031_stv2_time_to_tm(readl(ldata->base + RTC_DR),
			readl(ldata->base + RTC_YDR), tm);

	return 0;
}