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
struct platform_device {int dummy; } ;
struct dwc3_qcom {int hs_phy_irq; int dp_hs_phy_irq; int dm_hs_phy_irq; int ss_phy_irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct dwc3_qcom*) ; 
 int /*<<< orphan*/  irq_set_status_flags (int,int /*<<< orphan*/ ) ; 
 struct dwc3_qcom* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  qcom_dwc3_resume_irq ; 

__attribute__((used)) static int dwc3_qcom_setup_irq(struct platform_device *pdev)
{
	struct dwc3_qcom *qcom = platform_get_drvdata(pdev);
	int irq, ret;

	irq = platform_get_irq_byname(pdev, "hs_phy_irq");
	if (irq > 0) {
		/* Keep wakeup interrupts disabled until suspend */
		irq_set_status_flags(irq, IRQ_NOAUTOEN);
		ret = devm_request_threaded_irq(qcom->dev, irq, NULL,
					qcom_dwc3_resume_irq,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"qcom_dwc3 HS", qcom);
		if (ret) {
			dev_err(qcom->dev, "hs_phy_irq failed: %d\n", ret);
			return ret;
		}
		qcom->hs_phy_irq = irq;
	}

	irq = platform_get_irq_byname(pdev, "dp_hs_phy_irq");
	if (irq > 0) {
		irq_set_status_flags(irq, IRQ_NOAUTOEN);
		ret = devm_request_threaded_irq(qcom->dev, irq, NULL,
					qcom_dwc3_resume_irq,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"qcom_dwc3 DP_HS", qcom);
		if (ret) {
			dev_err(qcom->dev, "dp_hs_phy_irq failed: %d\n", ret);
			return ret;
		}
		qcom->dp_hs_phy_irq = irq;
	}

	irq = platform_get_irq_byname(pdev, "dm_hs_phy_irq");
	if (irq > 0) {
		irq_set_status_flags(irq, IRQ_NOAUTOEN);
		ret = devm_request_threaded_irq(qcom->dev, irq, NULL,
					qcom_dwc3_resume_irq,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"qcom_dwc3 DM_HS", qcom);
		if (ret) {
			dev_err(qcom->dev, "dm_hs_phy_irq failed: %d\n", ret);
			return ret;
		}
		qcom->dm_hs_phy_irq = irq;
	}

	irq = platform_get_irq_byname(pdev, "ss_phy_irq");
	if (irq > 0) {
		irq_set_status_flags(irq, IRQ_NOAUTOEN);
		ret = devm_request_threaded_irq(qcom->dev, irq, NULL,
					qcom_dwc3_resume_irq,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"qcom_dwc3 SS", qcom);
		if (ret) {
			dev_err(qcom->dev, "ss_phy_irq failed: %d\n", ret);
			return ret;
		}
		qcom->ss_phy_irq = irq;
	}

	return 0;
}