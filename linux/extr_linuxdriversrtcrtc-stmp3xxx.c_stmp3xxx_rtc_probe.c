#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct stmp3xxx_rtc_data {int irq_alarm; int /*<<< orphan*/  rtc; scalar_t__ io; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ STMP3XXX_RTC_CTRL ; 
 int STMP3XXX_RTC_CTRL_ALARM_IRQ_EN ; 
 int STMP3XXX_RTC_CTRL_ONEMSEC_IRQ_EN ; 
 int STMP3XXX_RTC_CTRL_WATCHDOGEN ; 
 scalar_t__ STMP3XXX_RTC_PERSISTENT0 ; 
 int STMP3XXX_RTC_PERSISTENT0_ALARM_EN ; 
 int STMP3XXX_RTC_PERSISTENT0_ALARM_WAKE ; 
 int STMP3XXX_RTC_PERSISTENT0_ALARM_WAKE_EN ; 
 int STMP3XXX_RTC_PERSISTENT0_CLOCKSOURCE ; 
 int STMP3XXX_RTC_PERSISTENT0_XTAL24MHZ_PWRUP ; 
 int STMP3XXX_RTC_PERSISTENT0_XTAL32KHZ_PWRUP ; 
 int STMP3XXX_RTC_PERSISTENT0_XTAL32_FREQ ; 
 scalar_t__ STMP3XXX_RTC_STAT ; 
 int STMP3XXX_RTC_STAT_RTC_PRESENT ; 
 int STMP3XXX_RTC_STAT_XTAL32000_PRESENT ; 
 int STMP3XXX_RTC_STAT_XTAL32768_PRESENT ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 scalar_t__ STMP_OFFSET_REG_SET ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 scalar_t__ devm_ioremap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stmp3xxx_rtc_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stmp3xxx_rtc_data*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  stmp3xxx_rtc_interrupt ; 
 int /*<<< orphan*/  stmp3xxx_rtc_ops ; 
 int /*<<< orphan*/  stmp3xxx_wdt_register (struct platform_device*) ; 
 int stmp_reset_block (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int stmp3xxx_rtc_probe(struct platform_device *pdev)
{
	struct stmp3xxx_rtc_data *rtc_data;
	struct resource *r;
	u32 rtc_stat;
	u32 pers0_set, pers0_clr;
	u32 crystalfreq = 0;
	int err;

	rtc_data = devm_kzalloc(&pdev->dev, sizeof(*rtc_data), GFP_KERNEL);
	if (!rtc_data)
		return -ENOMEM;

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r) {
		dev_err(&pdev->dev, "failed to get resource\n");
		return -ENXIO;
	}

	rtc_data->io = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	if (!rtc_data->io) {
		dev_err(&pdev->dev, "ioremap failed\n");
		return -EIO;
	}

	rtc_data->irq_alarm = platform_get_irq(pdev, 0);

	rtc_stat = readl(rtc_data->io + STMP3XXX_RTC_STAT);
	if (!(rtc_stat & STMP3XXX_RTC_STAT_RTC_PRESENT)) {
		dev_err(&pdev->dev, "no device onboard\n");
		return -ENODEV;
	}

	platform_set_drvdata(pdev, rtc_data);

	/*
	 * Resetting the rtc stops the watchdog timer that is potentially
	 * running. So (assuming it is running on purpose) don't reset if the
	 * watchdog is enabled.
	 */
	if (readl(rtc_data->io + STMP3XXX_RTC_CTRL) &
	    STMP3XXX_RTC_CTRL_WATCHDOGEN) {
		dev_info(&pdev->dev,
			 "Watchdog is running, skip resetting rtc\n");
	} else {
		err = stmp_reset_block(rtc_data->io);
		if (err) {
			dev_err(&pdev->dev, "stmp_reset_block failed: %d\n",
				err);
			return err;
		}
	}

	/*
	 * Obviously the rtc needs a clock input to be able to run.
	 * This clock can be provided by an external 32k crystal. If that one is
	 * missing XTAL must not be disabled in suspend which consumes a
	 * lot of power. Normally the presence and exact frequency (supported
	 * are 32000 Hz and 32768 Hz) is detectable from fuses, but as reality
	 * proves these fuses are not blown correctly on all machines, so the
	 * frequency can be overridden in the device tree.
	 */
	if (rtc_stat & STMP3XXX_RTC_STAT_XTAL32000_PRESENT)
		crystalfreq = 32000;
	else if (rtc_stat & STMP3XXX_RTC_STAT_XTAL32768_PRESENT)
		crystalfreq = 32768;

	of_property_read_u32(pdev->dev.of_node, "stmp,crystal-freq",
			     &crystalfreq);

	switch (crystalfreq) {
	case 32000:
		/* keep 32kHz crystal running in low-power mode */
		pers0_set = STMP3XXX_RTC_PERSISTENT0_XTAL32_FREQ |
			STMP3XXX_RTC_PERSISTENT0_XTAL32KHZ_PWRUP |
			STMP3XXX_RTC_PERSISTENT0_CLOCKSOURCE;
		pers0_clr = STMP3XXX_RTC_PERSISTENT0_XTAL24MHZ_PWRUP;
		break;
	case 32768:
		/* keep 32.768kHz crystal running in low-power mode */
		pers0_set = STMP3XXX_RTC_PERSISTENT0_XTAL32KHZ_PWRUP |
			STMP3XXX_RTC_PERSISTENT0_CLOCKSOURCE;
		pers0_clr = STMP3XXX_RTC_PERSISTENT0_XTAL24MHZ_PWRUP |
			STMP3XXX_RTC_PERSISTENT0_XTAL32_FREQ;
		break;
	default:
		dev_warn(&pdev->dev,
			 "invalid crystal-freq specified in device-tree. Assuming no crystal\n");
		/* fall-through */
	case 0:
		/* keep XTAL on in low-power mode */
		pers0_set = STMP3XXX_RTC_PERSISTENT0_XTAL24MHZ_PWRUP;
		pers0_clr = STMP3XXX_RTC_PERSISTENT0_XTAL32KHZ_PWRUP |
			STMP3XXX_RTC_PERSISTENT0_CLOCKSOURCE;
	}

	writel(pers0_set, rtc_data->io + STMP3XXX_RTC_PERSISTENT0 +
			STMP_OFFSET_REG_SET);

	writel(STMP3XXX_RTC_PERSISTENT0_ALARM_EN |
			STMP3XXX_RTC_PERSISTENT0_ALARM_WAKE_EN |
			STMP3XXX_RTC_PERSISTENT0_ALARM_WAKE | pers0_clr,
		rtc_data->io + STMP3XXX_RTC_PERSISTENT0 + STMP_OFFSET_REG_CLR);

	writel(STMP3XXX_RTC_CTRL_ONEMSEC_IRQ_EN |
			STMP3XXX_RTC_CTRL_ALARM_IRQ_EN,
		rtc_data->io + STMP3XXX_RTC_CTRL + STMP_OFFSET_REG_CLR);

	rtc_data->rtc = devm_rtc_device_register(&pdev->dev, pdev->name,
				&stmp3xxx_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc_data->rtc))
		return PTR_ERR(rtc_data->rtc);

	err = devm_request_irq(&pdev->dev, rtc_data->irq_alarm,
			stmp3xxx_rtc_interrupt, 0, "RTC alarm", &pdev->dev);
	if (err) {
		dev_err(&pdev->dev, "Cannot claim IRQ%d\n",
			rtc_data->irq_alarm);
		return err;
	}

	stmp3xxx_wdt_register(pdev);
	return 0;
}