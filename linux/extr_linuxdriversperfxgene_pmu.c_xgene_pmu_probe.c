#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xgene_pmu_data {int id; } ;
struct xgene_pmu {int version; int mcb_active_mask; int mc_active_mask; TYPE_1__* ops; int /*<<< orphan*/  cpu; int /*<<< orphan*/  lock; int /*<<< orphan*/  pcppmu_csr; int /*<<< orphan*/  mcpmus; int /*<<< orphan*/  mcbpmus; int /*<<< orphan*/  iobpmus; int /*<<< orphan*/  l3cpmus; int /*<<< orphan*/ * dev; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unmask_int ) (struct xgene_pmu*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_NOBALANCING ; 
 int IRQF_NO_THREAD ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PCP_PMU_V3 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct xgene_pmu* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct xgene_pmu*) ; 
 int irq_set_affinity (int,int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct xgene_pmu*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (struct xgene_pmu*) ; 
 int /*<<< orphan*/  xgene_pmu_isr ; 
 int /*<<< orphan*/  xgene_pmu_of_match ; 
 TYPE_1__ xgene_pmu_ops ; 
 int xgene_pmu_probe_active_mcb_mcu_l3c (struct xgene_pmu*,struct platform_device*) ; 
 int xgene_pmu_probe_pmu_dev (struct xgene_pmu*,struct platform_device*) ; 
 TYPE_1__ xgene_pmu_v3_ops ; 

__attribute__((used)) static int xgene_pmu_probe(struct platform_device *pdev)
{
	const struct xgene_pmu_data *dev_data;
	const struct of_device_id *of_id;
	struct xgene_pmu *xgene_pmu;
	struct resource *res;
	int irq, rc;
	int version;

	xgene_pmu = devm_kzalloc(&pdev->dev, sizeof(*xgene_pmu), GFP_KERNEL);
	if (!xgene_pmu)
		return -ENOMEM;
	xgene_pmu->dev = &pdev->dev;
	platform_set_drvdata(pdev, xgene_pmu);

	version = -EINVAL;
	of_id = of_match_device(xgene_pmu_of_match, &pdev->dev);
	if (of_id) {
		dev_data = (const struct xgene_pmu_data *) of_id->data;
		version = dev_data->id;
	}

#ifdef CONFIG_ACPI
	if (ACPI_COMPANION(&pdev->dev)) {
		const struct acpi_device_id *acpi_id;

		acpi_id = acpi_match_device(xgene_pmu_acpi_match, &pdev->dev);
		if (acpi_id)
			version = (int) acpi_id->driver_data;
	}
#endif
	if (version < 0)
		return -ENODEV;

	if (version == PCP_PMU_V3)
		xgene_pmu->ops = &xgene_pmu_v3_ops;
	else
		xgene_pmu->ops = &xgene_pmu_ops;

	INIT_LIST_HEAD(&xgene_pmu->l3cpmus);
	INIT_LIST_HEAD(&xgene_pmu->iobpmus);
	INIT_LIST_HEAD(&xgene_pmu->mcbpmus);
	INIT_LIST_HEAD(&xgene_pmu->mcpmus);

	xgene_pmu->version = version;
	dev_info(&pdev->dev, "X-Gene PMU version %d\n", xgene_pmu->version);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	xgene_pmu->pcppmu_csr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(xgene_pmu->pcppmu_csr)) {
		dev_err(&pdev->dev, "ioremap failed for PCP PMU resource\n");
		return PTR_ERR(xgene_pmu->pcppmu_csr);
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(&pdev->dev, "No IRQ resource\n");
		return -EINVAL;
	}
	rc = devm_request_irq(&pdev->dev, irq, xgene_pmu_isr,
				IRQF_NOBALANCING | IRQF_NO_THREAD,
				dev_name(&pdev->dev), xgene_pmu);
	if (rc) {
		dev_err(&pdev->dev, "Could not request IRQ %d\n", irq);
		return rc;
	}

	raw_spin_lock_init(&xgene_pmu->lock);

	/* Check for active MCBs and MCUs */
	rc = xgene_pmu_probe_active_mcb_mcu_l3c(xgene_pmu, pdev);
	if (rc) {
		dev_warn(&pdev->dev, "Unknown MCB/MCU active status\n");
		xgene_pmu->mcb_active_mask = 0x1;
		xgene_pmu->mc_active_mask = 0x1;
	}

	/* Pick one core to use for cpumask attributes */
	cpumask_set_cpu(smp_processor_id(), &xgene_pmu->cpu);

	/* Make sure that the overflow interrupt is handled by this CPU */
	rc = irq_set_affinity(irq, &xgene_pmu->cpu);
	if (rc) {
		dev_err(&pdev->dev, "Failed to set interrupt affinity!\n");
		return rc;
	}

	/* Walk through the tree for all PMU perf devices */
	rc = xgene_pmu_probe_pmu_dev(xgene_pmu, pdev);
	if (rc) {
		dev_err(&pdev->dev, "No PMU perf devices found!\n");
		return rc;
	}

	/* Enable interrupt */
	xgene_pmu->ops->unmask_int(xgene_pmu);

	return 0;
}