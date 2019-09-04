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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ips_driver {int second_cpu; int mcp_power_limit; int core_power_limit; int poll_turbo_status; int gpu_turbo_enabled; int orig_turbo_limit; int cpu_turbo_enabled; int mcp_temp_limit; int /*<<< orphan*/  irq; int /*<<< orphan*/  adjust; int /*<<< orphan*/  monitor; void* mgta_val; void* pta_val; void* cta_val; int /*<<< orphan*/  regmap; int /*<<< orphan*/  limits; int /*<<< orphan*/ * dev; int /*<<< orphan*/  turbo_status_lock; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HTS2_PRST_RUNNING ; 
 int HTS2_PRST_SHIFT ; 
 int HTS_NVV ; 
 int HTS_PCPL_SHIFT ; 
 int HTS_PTL_SHIFT ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_IRQ_LEGACY ; 
 int /*<<< orphan*/  PLATFORM_INFO ; 
 int PLATFORM_TDP ; 
 int PSP_PBRT ; 
 int TEN_UPDATE_EN ; 
 int /*<<< orphan*/  THM_CTA ; 
 int /*<<< orphan*/  THM_HTS ; 
 int /*<<< orphan*/  THM_HTSHI ; 
 int /*<<< orphan*/  THM_MGTA ; 
 int /*<<< orphan*/  THM_PSC ; 
 int /*<<< orphan*/  THM_PTA ; 
 int /*<<< orphan*/  THM_TEN ; 
 int /*<<< orphan*/  THM_TRC ; 
 int /*<<< orphan*/  THM_TSE ; 
 int /*<<< orphan*/  THM_TSPIEN ; 
 int TRC_CORE1_EN ; 
 int TRC_CORE2_EN ; 
 int TRC_CORE_PWR ; 
 int TRC_MCH_EN ; 
 scalar_t__ TSE_EN ; 
 int TSPIEN_AUX2_LOHI ; 
 int TSPIEN_AUX_LOHI ; 
 int TSPIEN_CRIT_LOHI ; 
 int TSPIEN_HOT_LOHI ; 
 int /*<<< orphan*/  TURBO_POWER_CURRENT_LIMIT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 struct ips_driver* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ips_driver*) ; 
 int /*<<< orphan*/  ips_adjust ; 
 int /*<<< orphan*/  ips_blacklist ; 
 int /*<<< orphan*/  ips_debugfs_init (struct ips_driver*) ; 
 int /*<<< orphan*/  ips_detect_cpu (struct ips_driver*) ; 
 int /*<<< orphan*/  ips_disable_cpu_turbo (struct ips_driver*) ; 
 int /*<<< orphan*/  ips_get_i915_syms (struct ips_driver*) ; 
 int /*<<< orphan*/  ips_irq_handler ; 
 int /*<<< orphan*/  ips_monitor ; 
 int /*<<< orphan*/  kthread_create (int /*<<< orphan*/ ,struct ips_driver*,char*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct ips_driver*,char*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct ips_driver*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcim_iomap_table (struct pci_dev*) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ips_driver*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ thm_readb (int /*<<< orphan*/ ) ; 
 int thm_readl (int /*<<< orphan*/ ) ; 
 void* thm_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thm_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thm_writel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thm_writew (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_turbo_limits (struct ips_driver*) ; 

__attribute__((used)) static int ips_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	u64 platform_info;
	struct ips_driver *ips;
	u32 hts;
	int ret = 0;
	u16 htshi, trc, trc_required_mask;
	u8 tse;

	if (dmi_check_system(ips_blacklist))
		return -ENODEV;

	ips = devm_kzalloc(&dev->dev, sizeof(*ips), GFP_KERNEL);
	if (!ips)
		return -ENOMEM;

	spin_lock_init(&ips->turbo_status_lock);
	ips->dev = &dev->dev;

	ips->limits = ips_detect_cpu(ips);
	if (!ips->limits) {
		dev_info(&dev->dev, "IPS not supported on this CPU\n");
		return -ENXIO;
	}

	ret = pcim_enable_device(dev);
	if (ret) {
		dev_err(&dev->dev, "can't enable PCI device, aborting\n");
		return ret;
	}

	ret = pcim_iomap_regions(dev, 1 << 0, pci_name(dev));
	if (ret) {
		dev_err(&dev->dev, "failed to map thermal regs, aborting\n");
		return ret;
	}
	ips->regmap = pcim_iomap_table(dev)[0];

	pci_set_drvdata(dev, ips);

	tse = thm_readb(THM_TSE);
	if (tse != TSE_EN) {
		dev_err(&dev->dev, "thermal device not enabled (0x%02x), aborting\n", tse);
		return -ENXIO;
	}

	trc = thm_readw(THM_TRC);
	trc_required_mask = TRC_CORE1_EN | TRC_CORE_PWR | TRC_MCH_EN;
	if ((trc & trc_required_mask) != trc_required_mask) {
		dev_err(&dev->dev, "thermal reporting for required devices not enabled, aborting\n");
		return -ENXIO;
	}

	if (trc & TRC_CORE2_EN)
		ips->second_cpu = true;

	update_turbo_limits(ips);
	dev_dbg(&dev->dev, "max cpu power clamp: %dW\n",
		ips->mcp_power_limit / 10);
	dev_dbg(&dev->dev, "max core power clamp: %dW\n",
		ips->core_power_limit / 10);
	/* BIOS may update limits at runtime */
	if (thm_readl(THM_PSC) & PSP_PBRT)
		ips->poll_turbo_status = true;

	if (!ips_get_i915_syms(ips)) {
		dev_info(&dev->dev, "failed to get i915 symbols, graphics turbo disabled until i915 loads\n");
		ips->gpu_turbo_enabled = false;
	} else {
		dev_dbg(&dev->dev, "graphics turbo enabled\n");
		ips->gpu_turbo_enabled = true;
	}

	/*
	 * Check PLATFORM_INFO MSR to make sure this chip is
	 * turbo capable.
	 */
	rdmsrl(PLATFORM_INFO, platform_info);
	if (!(platform_info & PLATFORM_TDP)) {
		dev_err(&dev->dev, "platform indicates TDP override unavailable, aborting\n");
		return -ENODEV;
	}

	/*
	 * IRQ handler for ME interaction
	 * Note: don't use MSI here as the PCH has bugs.
	 */
	ret = pci_alloc_irq_vectors(dev, 1, 1, PCI_IRQ_LEGACY);
	if (ret < 0)
		return ret;

	ips->irq = pci_irq_vector(dev, 0);

	ret = request_irq(ips->irq, ips_irq_handler, IRQF_SHARED, "ips", ips);
	if (ret) {
		dev_err(&dev->dev, "request irq failed, aborting\n");
		return ret;
	}

	/* Enable aux, hot & critical interrupts */
	thm_writeb(THM_TSPIEN, TSPIEN_AUX2_LOHI | TSPIEN_CRIT_LOHI |
		   TSPIEN_HOT_LOHI | TSPIEN_AUX_LOHI);
	thm_writeb(THM_TEN, TEN_UPDATE_EN);

	/* Collect adjustment values */
	ips->cta_val = thm_readw(THM_CTA);
	ips->pta_val = thm_readw(THM_PTA);
	ips->mgta_val = thm_readw(THM_MGTA);

	/* Save turbo limits & ratios */
	rdmsrl(TURBO_POWER_CURRENT_LIMIT, ips->orig_turbo_limit);

	ips_disable_cpu_turbo(ips);
	ips->cpu_turbo_enabled = false;

	/* Create thermal adjust thread */
	ips->adjust = kthread_create(ips_adjust, ips, "ips-adjust");
	if (IS_ERR(ips->adjust)) {
		dev_err(&dev->dev,
			"failed to create thermal adjust thread, aborting\n");
		ret = -ENOMEM;
		goto error_free_irq;

	}

	/*
	 * Set up the work queue and monitor thread. The monitor thread
	 * will wake up ips_adjust thread.
	 */
	ips->monitor = kthread_run(ips_monitor, ips, "ips-monitor");
	if (IS_ERR(ips->monitor)) {
		dev_err(&dev->dev,
			"failed to create thermal monitor thread, aborting\n");
		ret = -ENOMEM;
		goto error_thread_cleanup;
	}

	hts = (ips->core_power_limit << HTS_PCPL_SHIFT) |
		(ips->mcp_temp_limit << HTS_PTL_SHIFT) | HTS_NVV;
	htshi = HTS2_PRST_RUNNING << HTS2_PRST_SHIFT;

	thm_writew(THM_HTSHI, htshi);
	thm_writel(THM_HTS, hts);

	ips_debugfs_init(ips);

	dev_info(&dev->dev, "IPS driver initialized, MCP temp limit %d\n",
		 ips->mcp_temp_limit);
	return ret;

error_thread_cleanup:
	kthread_stop(ips->adjust);
error_free_irq:
	free_irq(ips->irq, ips);
	pci_free_irq_vectors(dev);
	return ret;
}