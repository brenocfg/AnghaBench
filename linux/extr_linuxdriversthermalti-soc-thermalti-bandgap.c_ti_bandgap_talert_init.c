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
struct ti_bandgap {scalar_t__ irq; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct ti_bandgap*) ; 
 int /*<<< orphan*/  ti_bandgap_talert_irq_handler ; 

__attribute__((used)) static int ti_bandgap_talert_init(struct ti_bandgap *bgp,
				  struct platform_device *pdev)
{
	int ret;

	bgp->irq = platform_get_irq(pdev, 0);
	if (bgp->irq < 0) {
		dev_err(&pdev->dev, "get_irq failed\n");
		return bgp->irq;
	}
	ret = request_threaded_irq(bgp->irq, NULL,
				   ti_bandgap_talert_irq_handler,
				   IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
				   "talert", bgp);
	if (ret) {
		dev_err(&pdev->dev, "Request threaded irq failed.\n");
		return ret;
	}

	return 0;
}