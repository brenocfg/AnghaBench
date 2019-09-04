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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct arm_spe_pmu {int irq; int /*<<< orphan*/  supported_cpus; struct platform_device* pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ irq_get_percpu_devid_partition (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_is_percpu (int) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arm_spe_pmu_irq_probe(struct arm_spe_pmu *spe_pmu)
{
	struct platform_device *pdev = spe_pmu->pdev;
	int irq = platform_get_irq(pdev, 0);

	if (irq < 0) {
		dev_err(&pdev->dev, "failed to get IRQ (%d)\n", irq);
		return -ENXIO;
	}

	if (!irq_is_percpu(irq)) {
		dev_err(&pdev->dev, "expected PPI but got SPI (%d)\n", irq);
		return -EINVAL;
	}

	if (irq_get_percpu_devid_partition(irq, &spe_pmu->supported_cpus)) {
		dev_err(&pdev->dev, "failed to get PPI partition (%d)\n", irq);
		return -EINVAL;
	}

	spe_pmu->irq = irq;
	return 0;
}