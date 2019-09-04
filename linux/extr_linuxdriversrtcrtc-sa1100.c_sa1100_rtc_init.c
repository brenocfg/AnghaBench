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
struct sa1100_rtc {int /*<<< orphan*/  rtsr; struct rtc_device* rtc; struct rtc_device* clk; int /*<<< orphan*/  rcnr; int /*<<< orphan*/  rttr; int /*<<< orphan*/  lock; } ;
struct rtc_device {int /*<<< orphan*/  max_user_freq; } ;
struct platform_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 int RTC_DEF_DIVIDER ; 
 int RTC_DEF_TRIM ; 
 int /*<<< orphan*/  RTC_FREQ ; 
 int RTSR_AL ; 
 int RTSR_HZ ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct rtc_device*) ; 
 int clk_prepare_enable (struct rtc_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct rtc_device* devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rtc_device* devm_rtc_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1100_rtc_ops ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

int sa1100_rtc_init(struct platform_device *pdev, struct sa1100_rtc *info)
{
	struct rtc_device *rtc;
	int ret;

	spin_lock_init(&info->lock);

	info->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(info->clk)) {
		dev_err(&pdev->dev, "failed to find rtc clock source\n");
		return PTR_ERR(info->clk);
	}

	ret = clk_prepare_enable(info->clk);
	if (ret)
		return ret;
	/*
	 * According to the manual we should be able to let RTTR be zero
	 * and then a default diviser for a 32.768KHz clock is used.
	 * Apparently this doesn't work, at least for my SA1110 rev 5.
	 * If the clock divider is uninitialized then reset it to the
	 * default value to get the 1Hz clock.
	 */
	if (readl_relaxed(info->rttr) == 0) {
		writel_relaxed(RTC_DEF_DIVIDER + (RTC_DEF_TRIM << 16), info->rttr);
		dev_warn(&pdev->dev, "warning: "
			"initializing default clock divider/trim value\n");
		/* The current RTC value probably doesn't make sense either */
		writel_relaxed(0, info->rcnr);
	}

	rtc = devm_rtc_device_register(&pdev->dev, pdev->name, &sa1100_rtc_ops,
					THIS_MODULE);
	if (IS_ERR(rtc)) {
		clk_disable_unprepare(info->clk);
		return PTR_ERR(rtc);
	}
	info->rtc = rtc;

	rtc->max_user_freq = RTC_FREQ;

	/* Fix for a nasty initialization problem the in SA11xx RTSR register.
	 * See also the comments in sa1100_rtc_interrupt().
	 *
	 * Sometimes bit 1 of the RTSR (RTSR_HZ) will wake up 1, which means an
	 * interrupt pending, even though interrupts were never enabled.
	 * In this case, this bit it must be reset before enabling
	 * interruptions to avoid a nonexistent interrupt to occur.
	 *
	 * In principle, the same problem would apply to bit 0, although it has
	 * never been observed to happen.
	 *
	 * This issue is addressed both here and in sa1100_rtc_interrupt().
	 * If the issue is not addressed here, in the times when the processor
	 * wakes up with the bit set there will be one spurious interrupt.
	 *
	 * The issue is also dealt with in sa1100_rtc_interrupt() to be on the
	 * safe side, once the condition that lead to this strange
	 * initialization is unknown and could in principle happen during
	 * normal processing.
	 *
	 * Notice that clearing bit 1 and 0 is accomplished by writting ONES to
	 * the corresponding bits in RTSR. */
	writel_relaxed(RTSR_AL | RTSR_HZ, info->rtsr);

	return 0;
}