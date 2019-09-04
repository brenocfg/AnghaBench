#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct rk808_rtc {int irq; TYPE_1__* rtc; struct rk808* rk808; } ;
struct rk808 {int /*<<< orphan*/  regmap; } ;
struct TYPE_11__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_10__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int BIT_RTC_CTRL_REG_RTC_READSEL_M ; 
 int BIT_RTC_CTRL_REG_STOP_RTC_M ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  RK808_RTC_CTRL_REG ; 
 int /*<<< orphan*/  RK808_RTC_STATUS_REG ; 
 int /*<<< orphan*/  RTC_STATUS_MASK ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int,...) ; 
 struct rk808* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_3__*,int) ; 
 struct rk808_rtc* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct rk808_rtc*) ; 
 TYPE_1__* devm_rtc_allocate_device (TYPE_3__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rk808_rtc*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk808_alarm_irq ; 
 int /*<<< orphan*/  rk808_rtc_ops ; 
 int rtc_register_device (TYPE_1__*) ; 

__attribute__((used)) static int rk808_rtc_probe(struct platform_device *pdev)
{
	struct rk808 *rk808 = dev_get_drvdata(pdev->dev.parent);
	struct rk808_rtc *rk808_rtc;
	int ret;

	rk808_rtc = devm_kzalloc(&pdev->dev, sizeof(*rk808_rtc), GFP_KERNEL);
	if (rk808_rtc == NULL)
		return -ENOMEM;

	platform_set_drvdata(pdev, rk808_rtc);
	rk808_rtc->rk808 = rk808;

	/* start rtc running by default, and use shadowed timer. */
	ret = regmap_update_bits(rk808->regmap, RK808_RTC_CTRL_REG,
				 BIT_RTC_CTRL_REG_STOP_RTC_M |
				 BIT_RTC_CTRL_REG_RTC_READSEL_M,
				 BIT_RTC_CTRL_REG_RTC_READSEL_M);
	if (ret) {
		dev_err(&pdev->dev,
			"Failed to update RTC control: %d\n", ret);
		return ret;
	}

	ret = regmap_write(rk808->regmap, RK808_RTC_STATUS_REG,
			   RTC_STATUS_MASK);
	if (ret) {
		dev_err(&pdev->dev,
			"Failed to write RTC status: %d\n", ret);
			return ret;
	}

	device_init_wakeup(&pdev->dev, 1);

	rk808_rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(rk808_rtc->rtc))
		return PTR_ERR(rk808_rtc->rtc);

	rk808_rtc->rtc->ops = &rk808_rtc_ops;

	rk808_rtc->irq = platform_get_irq(pdev, 0);
	if (rk808_rtc->irq < 0) {
		if (rk808_rtc->irq != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Wake up is not possible as irq = %d\n",
				rk808_rtc->irq);
		return rk808_rtc->irq;
	}

	/* request alarm irq of rk808 */
	ret = devm_request_threaded_irq(&pdev->dev, rk808_rtc->irq, NULL,
					rk808_alarm_irq, 0,
					"RTC alarm", rk808_rtc);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request alarm IRQ %d: %d\n",
			rk808_rtc->irq, ret);
		return ret;
	}

	return rtc_register_device(rk808_rtc->rtc);
}