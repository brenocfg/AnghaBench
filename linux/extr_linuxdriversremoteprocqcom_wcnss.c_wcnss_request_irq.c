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
struct qcom_wcnss {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char const*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct qcom_wcnss*) ; 
 int platform_get_irq_byname (struct platform_device*,char const*) ; 

__attribute__((used)) static int wcnss_request_irq(struct qcom_wcnss *wcnss,
			     struct platform_device *pdev,
			     const char *name,
			     bool optional,
			     irq_handler_t thread_fn)
{
	int ret;

	ret = platform_get_irq_byname(pdev, name);
	if (ret < 0 && optional) {
		dev_dbg(&pdev->dev, "no %s IRQ defined, ignoring\n", name);
		return 0;
	} else if (ret < 0) {
		dev_err(&pdev->dev, "no %s IRQ defined\n", name);
		return ret;
	}

	ret = devm_request_threaded_irq(&pdev->dev, ret,
					NULL, thread_fn,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"wcnss", wcnss);
	if (ret)
		dev_err(&pdev->dev, "request %s IRQ failed\n", name);

	return ret;
}