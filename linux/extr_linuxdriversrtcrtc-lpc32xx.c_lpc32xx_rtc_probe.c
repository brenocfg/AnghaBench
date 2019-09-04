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
typedef  int u32 ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct lpc32xx_rtc {int irq; int /*<<< orphan*/  rtc; int /*<<< orphan*/  lock; int /*<<< orphan*/  rtc_base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC32XX_RTC_CTRL ; 
 int LPC32XX_RTC_CTRL_CNTR_DIS ; 
 int LPC32XX_RTC_CTRL_MATCH0 ; 
 int LPC32XX_RTC_CTRL_MATCH1 ; 
 int LPC32XX_RTC_CTRL_ONSW_FORCE_HI ; 
 int LPC32XX_RTC_CTRL_ONSW_MATCH0 ; 
 int LPC32XX_RTC_CTRL_ONSW_MATCH1 ; 
 int LPC32XX_RTC_CTRL_SW_RESET ; 
 int /*<<< orphan*/  LPC32XX_RTC_INTSTAT ; 
 int LPC32XX_RTC_INTSTAT_MATCH0 ; 
 int LPC32XX_RTC_INTSTAT_MATCH1 ; 
 int LPC32XX_RTC_INTSTAT_ONSW ; 
 int /*<<< orphan*/  LPC32XX_RTC_KEY ; 
 int LPC32XX_RTC_KEY_ONSW_LOADVAL ; 
 int /*<<< orphan*/  LPC32XX_RTC_MATCH0 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_NAME ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct lpc32xx_rtc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lpc32xx_rtc*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc32xx_rtc_alarm_interrupt ; 
 int /*<<< orphan*/  lpc32xx_rtc_ops ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lpc32xx_rtc*) ; 
 int rtc_readl (struct lpc32xx_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_writel (struct lpc32xx_rtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int lpc32xx_rtc_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct lpc32xx_rtc *rtc;
	int rtcirq;
	u32 tmp;

	rtcirq = platform_get_irq(pdev, 0);
	if (rtcirq < 0) {
		dev_warn(&pdev->dev, "Can't get interrupt resource\n");
		rtcirq = -1;
	}

	rtc = devm_kzalloc(&pdev->dev, sizeof(*rtc), GFP_KERNEL);
	if (unlikely(!rtc))
		return -ENOMEM;

	rtc->irq = rtcirq;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rtc->rtc_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(rtc->rtc_base))
		return PTR_ERR(rtc->rtc_base);

	spin_lock_init(&rtc->lock);

	/*
	 * The RTC is on a separate power domain and can keep it's state
	 * across a chip power cycle. If the RTC has never been previously
	 * setup, then set it up now for the first time.
	 */
	tmp = rtc_readl(rtc, LPC32XX_RTC_CTRL);
	if (rtc_readl(rtc, LPC32XX_RTC_KEY) != LPC32XX_RTC_KEY_ONSW_LOADVAL) {
		tmp &= ~(LPC32XX_RTC_CTRL_SW_RESET |
			LPC32XX_RTC_CTRL_CNTR_DIS |
			LPC32XX_RTC_CTRL_MATCH0 |
			LPC32XX_RTC_CTRL_MATCH1 |
			LPC32XX_RTC_CTRL_ONSW_MATCH0 |
			LPC32XX_RTC_CTRL_ONSW_MATCH1 |
			LPC32XX_RTC_CTRL_ONSW_FORCE_HI);
		rtc_writel(rtc, LPC32XX_RTC_CTRL, tmp);

		/* Clear latched interrupt states */
		rtc_writel(rtc, LPC32XX_RTC_MATCH0, 0xFFFFFFFF);
		rtc_writel(rtc, LPC32XX_RTC_INTSTAT,
			   LPC32XX_RTC_INTSTAT_MATCH0 |
			   LPC32XX_RTC_INTSTAT_MATCH1 |
			   LPC32XX_RTC_INTSTAT_ONSW);

		/* Write key value to RTC so it won't reload on reset */
		rtc_writel(rtc, LPC32XX_RTC_KEY,
			   LPC32XX_RTC_KEY_ONSW_LOADVAL);
	} else {
		rtc_writel(rtc, LPC32XX_RTC_CTRL,
			   tmp & ~LPC32XX_RTC_CTRL_MATCH0);
	}

	platform_set_drvdata(pdev, rtc);

	rtc->rtc = devm_rtc_device_register(&pdev->dev, RTC_NAME,
					&lpc32xx_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc->rtc)) {
		dev_err(&pdev->dev, "Can't get RTC\n");
		return PTR_ERR(rtc->rtc);
	}

	/*
	 * IRQ is enabled after device registration in case alarm IRQ
	 * is pending upon suspend exit.
	 */
	if (rtc->irq >= 0) {
		if (devm_request_irq(&pdev->dev, rtc->irq,
				     lpc32xx_rtc_alarm_interrupt,
				     0, pdev->name, rtc) < 0) {
			dev_warn(&pdev->dev, "Can't request interrupt.\n");
			rtc->irq = -1;
		} else {
			device_init_wakeup(&pdev->dev, 1);
		}
	}

	return 0;
}