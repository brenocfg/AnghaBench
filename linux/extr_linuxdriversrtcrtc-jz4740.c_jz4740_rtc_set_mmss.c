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
struct jz4740_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_REG_RTC_SEC ; 
 struct jz4740_rtc* dev_get_drvdata (struct device*) ; 
 int jz4740_rtc_reg_write (struct jz4740_rtc*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int jz4740_rtc_set_mmss(struct device *dev, unsigned long secs)
{
	struct jz4740_rtc *rtc = dev_get_drvdata(dev);

	return jz4740_rtc_reg_write(rtc, JZ_REG_RTC_SEC, secs);
}