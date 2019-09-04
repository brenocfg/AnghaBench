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
typedef  int /*<<< orphan*/  time64_t ;
struct rtc_time {int dummy; } ;
struct mxc_rtc_data {int /*<<< orphan*/  clk; scalar_t__ ioaddr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SRTC_LPSCMR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 struct mxc_rtc_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int /*<<< orphan*/  const,struct rtc_time*) ; 

__attribute__((used)) static int mxc_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct mxc_rtc_data *pdata = dev_get_drvdata(dev);
	const int clk_failed = clk_enable(pdata->clk);

	if (!clk_failed) {
		const time64_t now = readl(pdata->ioaddr + SRTC_LPSCMR);

		rtc_time64_to_tm(now, tm);
		clk_disable(pdata->clk);
		return 0;
	}
	return clk_failed;
}