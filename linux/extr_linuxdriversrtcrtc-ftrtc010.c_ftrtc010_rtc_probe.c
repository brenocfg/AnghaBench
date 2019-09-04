#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct ftrtc010_rtc {TYPE_1__* rtc_dev; int /*<<< orphan*/  rtc_irq; scalar_t__ rtc_base; TYPE_1__* extclk; TYPE_1__* pclk; } ;
struct TYPE_6__ {int range_min; int range_max; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ FTRTC010_RTC_DAYS ; 
 scalar_t__ FTRTC010_RTC_HOUR ; 
 scalar_t__ FTRTC010_RTC_MINUTE ; 
 scalar_t__ FTRTC010_RTC_SECOND ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int U32_MAX ; 
 int clk_prepare_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 scalar_t__ devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ftrtc010_rtc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*) ; 
 TYPE_1__* devm_rtc_allocate_device (struct device*) ; 
 int /*<<< orphan*/  ftrtc010_rtc_interrupt ; 
 int /*<<< orphan*/  ftrtc010_rtc_ops ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ftrtc010_rtc*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int rtc_register_device (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ftrtc010_rtc_probe(struct platform_device *pdev)
{
	u32 days, hour, min, sec;
	struct ftrtc010_rtc *rtc;
	struct device *dev = &pdev->dev;
	struct resource *res;
	int ret;

	rtc = devm_kzalloc(&pdev->dev, sizeof(*rtc), GFP_KERNEL);
	if (unlikely(!rtc))
		return -ENOMEM;
	platform_set_drvdata(pdev, rtc);

	rtc->pclk = devm_clk_get(dev, "PCLK");
	if (IS_ERR(rtc->pclk)) {
		dev_err(dev, "could not get PCLK\n");
	} else {
		ret = clk_prepare_enable(rtc->pclk);
		if (ret) {
			dev_err(dev, "failed to enable PCLK\n");
			return ret;
		}
	}
	rtc->extclk = devm_clk_get(dev, "EXTCLK");
	if (IS_ERR(rtc->extclk)) {
		dev_err(dev, "could not get EXTCLK\n");
	} else {
		ret = clk_prepare_enable(rtc->extclk);
		if (ret) {
			dev_err(dev, "failed to enable EXTCLK\n");
			return ret;
		}
	}

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res)
		return -ENODEV;

	rtc->rtc_irq = res->start;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;

	rtc->rtc_base = devm_ioremap(dev, res->start,
				     resource_size(res));
	if (!rtc->rtc_base)
		return -ENOMEM;

	rtc->rtc_dev = devm_rtc_allocate_device(dev);
	if (IS_ERR(rtc->rtc_dev))
		return PTR_ERR(rtc->rtc_dev);

	rtc->rtc_dev->ops = &ftrtc010_rtc_ops;

	sec  = readl(rtc->rtc_base + FTRTC010_RTC_SECOND);
	min  = readl(rtc->rtc_base + FTRTC010_RTC_MINUTE);
	hour = readl(rtc->rtc_base + FTRTC010_RTC_HOUR);
	days = readl(rtc->rtc_base + FTRTC010_RTC_DAYS);

	rtc->rtc_dev->range_min = (u64)days * 86400 + hour * 3600 +
				  min * 60 + sec;
	rtc->rtc_dev->range_max = U32_MAX + rtc->rtc_dev->range_min;

	ret = devm_request_irq(dev, rtc->rtc_irq, ftrtc010_rtc_interrupt,
			       IRQF_SHARED, pdev->name, dev);
	if (unlikely(ret))
		return ret;

	return rtc_register_device(rtc->rtc_dev);
}