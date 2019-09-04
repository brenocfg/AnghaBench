#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct resource {int dummy; } ;
struct platform_device_id {int driver_data; } ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct of_device_id {scalar_t__ data; } ;
struct jz4740_rtc {int type; scalar_t__ irq; int reset_pin_assert_time; int min_wakeup_pin_assert_time; int /*<<< orphan*/  rtc; int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; } ;
struct device_node {int dummy; } ;
typedef  enum jz4740_rtc_type { ____Placeholder_jz4740_rtc_type } jz4740_rtc_type ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_REG_RTC_SCRATCHPAD ; 
 int /*<<< orphan*/  JZ_REG_RTC_SEC ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 TYPE_1__* dev_for_power_off ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct jz4740_rtc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jz4740_rtc*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_rtc_irq ; 
 int /*<<< orphan*/  jz4740_rtc_of_match ; 
 int /*<<< orphan*/  jz4740_rtc_ops ; 
 scalar_t__ jz4740_rtc_power_off ; 
 int jz4740_rtc_reg_read (struct jz4740_rtc*,int /*<<< orphan*/ ) ; 
 int jz4740_rtc_reg_write (struct jz4740_rtc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ of_device_is_system_power_controller (struct device_node*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct jz4740_rtc*) ; 
 scalar_t__ pm_power_off ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jz4740_rtc_probe(struct platform_device *pdev)
{
	int ret;
	struct jz4740_rtc *rtc;
	uint32_t scratchpad;
	struct resource *mem;
	const struct platform_device_id *id = platform_get_device_id(pdev);
	const struct of_device_id *of_id = of_match_device(
			jz4740_rtc_of_match, &pdev->dev);
	struct device_node *np = pdev->dev.of_node;

	rtc = devm_kzalloc(&pdev->dev, sizeof(*rtc), GFP_KERNEL);
	if (!rtc)
		return -ENOMEM;

	if (of_id)
		rtc->type = (enum jz4740_rtc_type)of_id->data;
	else
		rtc->type = id->driver_data;

	rtc->irq = platform_get_irq(pdev, 0);
	if (rtc->irq < 0) {
		dev_err(&pdev->dev, "Failed to get platform irq\n");
		return -ENOENT;
	}

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rtc->base = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(rtc->base))
		return PTR_ERR(rtc->base);

	rtc->clk = devm_clk_get(&pdev->dev, "rtc");
	if (IS_ERR(rtc->clk)) {
		dev_err(&pdev->dev, "Failed to get RTC clock\n");
		return PTR_ERR(rtc->clk);
	}

	spin_lock_init(&rtc->lock);

	platform_set_drvdata(pdev, rtc);

	device_init_wakeup(&pdev->dev, 1);

	rtc->rtc = devm_rtc_device_register(&pdev->dev, pdev->name,
					&jz4740_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc->rtc)) {
		ret = PTR_ERR(rtc->rtc);
		dev_err(&pdev->dev, "Failed to register rtc device: %d\n", ret);
		return ret;
	}

	ret = devm_request_irq(&pdev->dev, rtc->irq, jz4740_rtc_irq, 0,
				pdev->name, rtc);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request rtc irq: %d\n", ret);
		return ret;
	}

	scratchpad = jz4740_rtc_reg_read(rtc, JZ_REG_RTC_SCRATCHPAD);
	if (scratchpad != 0x12345678) {
		ret = jz4740_rtc_reg_write(rtc, JZ_REG_RTC_SCRATCHPAD, 0x12345678);
		ret = jz4740_rtc_reg_write(rtc, JZ_REG_RTC_SEC, 0);
		if (ret) {
			dev_err(&pdev->dev, "Could not write to RTC registers\n");
			return ret;
		}
	}

	if (np && of_device_is_system_power_controller(np)) {
		if (!pm_power_off) {
			/* Default: 60ms */
			rtc->reset_pin_assert_time = 60;
			of_property_read_u32(np, "reset-pin-assert-time-ms",
					     &rtc->reset_pin_assert_time);

			/* Default: 100ms */
			rtc->min_wakeup_pin_assert_time = 100;
			of_property_read_u32(np,
					     "min-wakeup-pin-assert-time-ms",
					     &rtc->min_wakeup_pin_assert_time);

			dev_for_power_off = &pdev->dev;
			pm_power_off = jz4740_rtc_power_off;
		} else {
			dev_warn(&pdev->dev,
				 "Poweroff handler already present!\n");
		}
	}

	return 0;
}