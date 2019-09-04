#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dwc3_qcom {scalar_t__ pm_suspended; int /*<<< orphan*/  dwc3; } ;
struct dwc3 {TYPE_1__* xhci; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct dwc3* platform_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_resume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t qcom_dwc3_resume_irq(int irq, void *data)
{
	struct dwc3_qcom *qcom = data;
	struct dwc3	*dwc = platform_get_drvdata(qcom->dwc3);

	/* If pm_suspended then let pm_resume take care of resuming h/w */
	if (qcom->pm_suspended)
		return IRQ_HANDLED;

	if (dwc->xhci)
		pm_runtime_resume(&dwc->xhci->dev);

	return IRQ_HANDLED;
}