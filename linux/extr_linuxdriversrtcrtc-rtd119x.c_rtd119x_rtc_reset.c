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
typedef  int /*<<< orphan*/  u32 ;
struct rtd119x_rtc {scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTD_RTCCR ; 
 int /*<<< orphan*/  RTD_RTCCR_RTCRST ; 
 struct rtd119x_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rtd119x_rtc_reset(struct device *dev)
{
	struct rtd119x_rtc *data = dev_get_drvdata(dev);
	u32 val;

	val = readl_relaxed(data->base + RTD_RTCCR);
	val |= RTD_RTCCR_RTCRST;
	writel_relaxed(val, data->base + RTD_RTCCR);

	val &= ~RTD_RTCCR_RTCRST;
	writel(val, data->base + RTD_RTCCR);
}