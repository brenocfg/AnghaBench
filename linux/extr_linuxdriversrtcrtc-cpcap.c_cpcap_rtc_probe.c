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
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct cpcap_rtc {void* update_irq; void* alarm_irq; int /*<<< orphan*/  vendor; int /*<<< orphan*/  regmap; int /*<<< orphan*/  rtc_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_TRIGGER_NONE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cpcap_get_vendor (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpcap_rtc_alarm_irq ; 
 int /*<<< orphan*/  cpcap_rtc_ops ; 
 int /*<<< orphan*/  cpcap_rtc_update_irq ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int device_init_wakeup (struct device*,int) ; 
 struct cpcap_rtc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct cpcap_rtc*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (struct device*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (void*) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cpcap_rtc*) ; 

__attribute__((used)) static int cpcap_rtc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct cpcap_rtc *rtc;
	int err;

	rtc = devm_kzalloc(dev, sizeof(*rtc), GFP_KERNEL);
	if (!rtc)
		return -ENOMEM;

	rtc->regmap = dev_get_regmap(dev->parent, NULL);
	if (!rtc->regmap)
		return -ENODEV;

	platform_set_drvdata(pdev, rtc);
	rtc->rtc_dev = devm_rtc_device_register(dev, "cpcap_rtc",
						&cpcap_rtc_ops, THIS_MODULE);

	if (IS_ERR(rtc->rtc_dev))
		return PTR_ERR(rtc->rtc_dev);

	err = cpcap_get_vendor(dev, rtc->regmap, &rtc->vendor);
	if (err)
		return err;

	rtc->alarm_irq = platform_get_irq(pdev, 0);
	err = devm_request_threaded_irq(dev, rtc->alarm_irq, NULL,
					cpcap_rtc_alarm_irq, IRQF_TRIGGER_NONE,
					"rtc_alarm", rtc);
	if (err) {
		dev_err(dev, "Could not request alarm irq: %d\n", err);
		return err;
	}
	disable_irq(rtc->alarm_irq);

	/* Stock Android uses the 1 Hz interrupt for "secure clock daemon",
	 * which is not supported by the mainline kernel. The mainline kernel
	 * does not use the irq at the moment, but we explicitly request and
	 * disable it, so that its masked and does not wake up the processor
	 * every second.
	 */
	rtc->update_irq = platform_get_irq(pdev, 1);
	err = devm_request_threaded_irq(dev, rtc->update_irq, NULL,
					cpcap_rtc_update_irq, IRQF_TRIGGER_NONE,
					"rtc_1hz", rtc);
	if (err) {
		dev_err(dev, "Could not request update irq: %d\n", err);
		return err;
	}
	disable_irq(rtc->update_irq);

	err = device_init_wakeup(dev, 1);
	if (err) {
		dev_err(dev, "wakeup initialization failed (%d)\n", err);
		/* ignore error and continue without wakeup support */
	}

	return 0;
}