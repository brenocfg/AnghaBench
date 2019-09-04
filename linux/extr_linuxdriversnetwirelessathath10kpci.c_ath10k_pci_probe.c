#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_device_id {int device; } ;
struct pci_dev {int /*<<< orphan*/  device; int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  vendor; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * bus_ops; } ;
struct ath10k_pci {int pci_ps; int (* pci_soft_reset ) (struct ath10k*) ;int (* pci_hard_reset ) (struct ath10k*) ;int (* targ_cpu_to_ce_addr ) (struct ath10k*,int) ;int /*<<< orphan*/  oper_irq_mode; int /*<<< orphan*/  ps_timer; TYPE_1__ ce; struct ath10k* ar; int /*<<< orphan*/ * dev; struct pci_dev* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct ath10k {int dev_id; TYPE_2__ id; TYPE_1__* ce_priv; } ;
typedef  enum ath10k_hw_rev { ____Placeholder_ath10k_hw_rev } ath10k_hw_rev ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_BUS_PCI ; 
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int ATH10K_HW_QCA6174 ; 
 int ATH10K_HW_QCA9377 ; 
 int ATH10K_HW_QCA9887 ; 
 int ATH10K_HW_QCA9888 ; 
 int ATH10K_HW_QCA988X ; 
 int ATH10K_HW_QCA9984 ; 
 int ATH10K_HW_QCA99X0 ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
#define  QCA6164_2_1_DEVICE_ID 136 
#define  QCA6174_2_1_DEVICE_ID 135 
#define  QCA9377_1_0_DEVICE_ID 134 
#define  QCA9887_1_0_DEVICE_ID 133 
#define  QCA9888_2_0_DEVICE_ID 132 
#define  QCA988X_2_0_DEVICE_ID 131 
#define  QCA988X_2_0_DEVICE_ID_UBNT 130 
#define  QCA9984_1_0_DEVICE_ID 129 
#define  QCA99X0_2_0_DEVICE_ID 128 
 int /*<<< orphan*/  SOC_CHIP_ID_ADDRESS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ath10k* ath10k_core_create (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_core_destroy (struct ath10k*) ; 
 int ath10k_core_register (struct ath10k*,int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,...) ; 
 int /*<<< orphan*/  ath10k_info (struct ath10k*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_pci_bus_ops ; 
 int /*<<< orphan*/  ath10k_pci_ce_deinit (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_chip_is_supported (int /*<<< orphan*/ ,int) ; 
 int ath10k_pci_chip_reset (struct ath10k*) ; 
 int ath10k_pci_claim (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_deinit_irq (struct ath10k*) ; 
 int ath10k_pci_force_wake (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_free_irq (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_free_pipes (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_get_irq_method (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_hif_ops ; 
 int ath10k_pci_init_irq (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_irq_disable (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_irq_mode ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_ps_timer ; 
 int ath10k_pci_qca6174_chip_reset (struct ath10k*) ; 
 int ath10k_pci_qca988x_chip_reset (struct ath10k*) ; 
 int ath10k_pci_qca988x_targ_cpu_to_ce_addr (struct ath10k*,int) ; 
 int ath10k_pci_qca99x0_chip_reset (struct ath10k*) ; 
 int ath10k_pci_qca99x0_soft_chip_reset (struct ath10k*) ; 
 int ath10k_pci_qca99x0_targ_cpu_to_ce_addr (struct ath10k*,int) ; 
 int /*<<< orphan*/  ath10k_pci_release (struct ath10k*) ; 
 int ath10k_pci_request_irq (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_reset_mode ; 
 int /*<<< orphan*/  ath10k_pci_rx_retry_sync (struct ath10k*) ; 
 int ath10k_pci_setup_resource (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_sleep_sync (struct ath10k*) ; 
 int ath10k_pci_soc_read32 (struct ath10k*,int /*<<< orphan*/ ) ; 
 int ath10k_pci_warm_reset (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_pci_probe(struct pci_dev *pdev,
			    const struct pci_device_id *pci_dev)
{
	int ret = 0;
	struct ath10k *ar;
	struct ath10k_pci *ar_pci;
	enum ath10k_hw_rev hw_rev;
	u32 chip_id;
	bool pci_ps;
	int (*pci_soft_reset)(struct ath10k *ar);
	int (*pci_hard_reset)(struct ath10k *ar);
	u32 (*targ_cpu_to_ce_addr)(struct ath10k *ar, u32 addr);

	switch (pci_dev->device) {
	case QCA988X_2_0_DEVICE_ID_UBNT:
	case QCA988X_2_0_DEVICE_ID:
		hw_rev = ATH10K_HW_QCA988X;
		pci_ps = false;
		pci_soft_reset = ath10k_pci_warm_reset;
		pci_hard_reset = ath10k_pci_qca988x_chip_reset;
		targ_cpu_to_ce_addr = ath10k_pci_qca988x_targ_cpu_to_ce_addr;
		break;
	case QCA9887_1_0_DEVICE_ID:
		hw_rev = ATH10K_HW_QCA9887;
		pci_ps = false;
		pci_soft_reset = ath10k_pci_warm_reset;
		pci_hard_reset = ath10k_pci_qca988x_chip_reset;
		targ_cpu_to_ce_addr = ath10k_pci_qca988x_targ_cpu_to_ce_addr;
		break;
	case QCA6164_2_1_DEVICE_ID:
	case QCA6174_2_1_DEVICE_ID:
		hw_rev = ATH10K_HW_QCA6174;
		pci_ps = true;
		pci_soft_reset = ath10k_pci_warm_reset;
		pci_hard_reset = ath10k_pci_qca6174_chip_reset;
		targ_cpu_to_ce_addr = ath10k_pci_qca988x_targ_cpu_to_ce_addr;
		break;
	case QCA99X0_2_0_DEVICE_ID:
		hw_rev = ATH10K_HW_QCA99X0;
		pci_ps = false;
		pci_soft_reset = ath10k_pci_qca99x0_soft_chip_reset;
		pci_hard_reset = ath10k_pci_qca99x0_chip_reset;
		targ_cpu_to_ce_addr = ath10k_pci_qca99x0_targ_cpu_to_ce_addr;
		break;
	case QCA9984_1_0_DEVICE_ID:
		hw_rev = ATH10K_HW_QCA9984;
		pci_ps = false;
		pci_soft_reset = ath10k_pci_qca99x0_soft_chip_reset;
		pci_hard_reset = ath10k_pci_qca99x0_chip_reset;
		targ_cpu_to_ce_addr = ath10k_pci_qca99x0_targ_cpu_to_ce_addr;
		break;
	case QCA9888_2_0_DEVICE_ID:
		hw_rev = ATH10K_HW_QCA9888;
		pci_ps = false;
		pci_soft_reset = ath10k_pci_qca99x0_soft_chip_reset;
		pci_hard_reset = ath10k_pci_qca99x0_chip_reset;
		targ_cpu_to_ce_addr = ath10k_pci_qca99x0_targ_cpu_to_ce_addr;
		break;
	case QCA9377_1_0_DEVICE_ID:
		hw_rev = ATH10K_HW_QCA9377;
		pci_ps = true;
		pci_soft_reset = NULL;
		pci_hard_reset = ath10k_pci_qca6174_chip_reset;
		targ_cpu_to_ce_addr = ath10k_pci_qca988x_targ_cpu_to_ce_addr;
		break;
	default:
		WARN_ON(1);
		return -ENOTSUPP;
	}

	ar = ath10k_core_create(sizeof(*ar_pci), &pdev->dev, ATH10K_BUS_PCI,
				hw_rev, &ath10k_pci_hif_ops);
	if (!ar) {
		dev_err(&pdev->dev, "failed to allocate core\n");
		return -ENOMEM;
	}

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "pci probe %04x:%04x %04x:%04x\n",
		   pdev->vendor, pdev->device,
		   pdev->subsystem_vendor, pdev->subsystem_device);

	ar_pci = ath10k_pci_priv(ar);
	ar_pci->pdev = pdev;
	ar_pci->dev = &pdev->dev;
	ar_pci->ar = ar;
	ar->dev_id = pci_dev->device;
	ar_pci->pci_ps = pci_ps;
	ar_pci->ce.bus_ops = &ath10k_pci_bus_ops;
	ar_pci->pci_soft_reset = pci_soft_reset;
	ar_pci->pci_hard_reset = pci_hard_reset;
	ar_pci->targ_cpu_to_ce_addr = targ_cpu_to_ce_addr;
	ar->ce_priv = &ar_pci->ce;

	ar->id.vendor = pdev->vendor;
	ar->id.device = pdev->device;
	ar->id.subsystem_vendor = pdev->subsystem_vendor;
	ar->id.subsystem_device = pdev->subsystem_device;

	timer_setup(&ar_pci->ps_timer, ath10k_pci_ps_timer, 0);

	ret = ath10k_pci_setup_resource(ar);
	if (ret) {
		ath10k_err(ar, "failed to setup resource: %d\n", ret);
		goto err_core_destroy;
	}

	ret = ath10k_pci_claim(ar);
	if (ret) {
		ath10k_err(ar, "failed to claim device: %d\n", ret);
		goto err_free_pipes;
	}

	ret = ath10k_pci_force_wake(ar);
	if (ret) {
		ath10k_warn(ar, "failed to wake up device : %d\n", ret);
		goto err_sleep;
	}

	ath10k_pci_ce_deinit(ar);
	ath10k_pci_irq_disable(ar);

	ret = ath10k_pci_init_irq(ar);
	if (ret) {
		ath10k_err(ar, "failed to init irqs: %d\n", ret);
		goto err_sleep;
	}

	ath10k_info(ar, "pci irq %s oper_irq_mode %d irq_mode %d reset_mode %d\n",
		    ath10k_pci_get_irq_method(ar), ar_pci->oper_irq_mode,
		    ath10k_pci_irq_mode, ath10k_pci_reset_mode);

	ret = ath10k_pci_request_irq(ar);
	if (ret) {
		ath10k_warn(ar, "failed to request irqs: %d\n", ret);
		goto err_deinit_irq;
	}

	ret = ath10k_pci_chip_reset(ar);
	if (ret) {
		ath10k_err(ar, "failed to reset chip: %d\n", ret);
		goto err_free_irq;
	}

	chip_id = ath10k_pci_soc_read32(ar, SOC_CHIP_ID_ADDRESS);
	if (chip_id == 0xffffffff) {
		ath10k_err(ar, "failed to get chip id\n");
		goto err_free_irq;
	}

	if (!ath10k_pci_chip_is_supported(pdev->device, chip_id)) {
		ath10k_err(ar, "device %04x with chip_id %08x isn't supported\n",
			   pdev->device, chip_id);
		goto err_free_irq;
	}

	ret = ath10k_core_register(ar, chip_id);
	if (ret) {
		ath10k_err(ar, "failed to register driver core: %d\n", ret);
		goto err_free_irq;
	}

	return 0;

err_free_irq:
	ath10k_pci_free_irq(ar);
	ath10k_pci_rx_retry_sync(ar);

err_deinit_irq:
	ath10k_pci_deinit_irq(ar);

err_sleep:
	ath10k_pci_sleep_sync(ar);
	ath10k_pci_release(ar);

err_free_pipes:
	ath10k_pci_free_pipes(ar);

err_core_destroy:
	ath10k_core_destroy(ar);

	return ret;
}