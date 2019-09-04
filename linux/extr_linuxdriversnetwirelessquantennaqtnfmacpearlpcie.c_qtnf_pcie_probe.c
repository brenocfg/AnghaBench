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
struct qtnf_pcie_bus_priv {int /*<<< orphan*/  reclaim_tq; int /*<<< orphan*/  workqueue; scalar_t__ tx_reclaim_req; scalar_t__ tx_reclaim_done; scalar_t__ pcie_irq_uf_count; scalar_t__ pcie_irq_tx_count; scalar_t__ pcie_irq_rx_count; scalar_t__ pcie_irq_count; scalar_t__ tx_done_count; scalar_t__ tx_full_count; int /*<<< orphan*/  tx_reclaim_lock; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  tx0_lock; struct pci_dev* pdev; } ;
struct qtnf_bus {int /*<<< orphan*/  mux_napi; int /*<<< orphan*/  mux_dev; int /*<<< orphan*/  bus_lock; int /*<<< orphan*/  firmware_init_complete; int /*<<< orphan*/  fwname; int /*<<< orphan*/  fw_state; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * bus_ops; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QTNF_FW_STATE_RESET ; 
 int /*<<< orphan*/  QTN_PCI_PEARL_FW_NAME ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct qtnf_bus* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,void*) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 struct qtnf_pcie_bus_priv* get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_dummy_netdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct qtnf_bus*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  qtnf_bringup_fw_async (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_disable_hdp_irqs (struct qtnf_pcie_bus_priv*) ; 
 int /*<<< orphan*/  qtnf_free_xfer_buffers (struct qtnf_pcie_bus_priv*) ; 
 int /*<<< orphan*/  qtnf_init_hdp_irqs (struct qtnf_pcie_bus_priv*) ; 
 int /*<<< orphan*/  qtnf_interrupt ; 
 int /*<<< orphan*/  qtnf_pcie_bus_ops ; 
 int /*<<< orphan*/  qtnf_pcie_free_shm_ipc (struct qtnf_pcie_bus_priv*) ; 
 int /*<<< orphan*/  qtnf_pcie_init_irq (struct qtnf_pcie_bus_priv*) ; 
 int qtnf_pcie_init_memory (struct qtnf_pcie_bus_priv*) ; 
 int qtnf_pcie_init_shm_ipc (struct qtnf_pcie_bus_priv*) ; 
 int qtnf_pcie_init_xfer (struct qtnf_pcie_bus_priv*) ; 
 int /*<<< orphan*/  qtnf_reclaim_tasklet_fn ; 
 int /*<<< orphan*/  qtnf_rx_poll ; 
 int /*<<< orphan*/  qtnf_tune_pcie_mps (struct qtnf_pcie_bus_priv*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qtnf_pcie_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct qtnf_pcie_bus_priv *pcie_priv;
	struct qtnf_bus *bus;
	int ret;

	bus = devm_kzalloc(&pdev->dev,
			   sizeof(*bus) + sizeof(*pcie_priv), GFP_KERNEL);
	if (!bus)
		return -ENOMEM;

	pcie_priv = get_bus_priv(bus);

	pci_set_drvdata(pdev, bus);
	bus->bus_ops = &qtnf_pcie_bus_ops;
	bus->dev = &pdev->dev;
	bus->fw_state = QTNF_FW_STATE_RESET;
	pcie_priv->pdev = pdev;

	strcpy(bus->fwname, QTN_PCI_PEARL_FW_NAME);
	init_completion(&bus->firmware_init_complete);
	mutex_init(&bus->bus_lock);
	spin_lock_init(&pcie_priv->tx0_lock);
	spin_lock_init(&pcie_priv->irq_lock);
	spin_lock_init(&pcie_priv->tx_reclaim_lock);

	/* init stats */
	pcie_priv->tx_full_count = 0;
	pcie_priv->tx_done_count = 0;
	pcie_priv->pcie_irq_count = 0;
	pcie_priv->pcie_irq_rx_count = 0;
	pcie_priv->pcie_irq_tx_count = 0;
	pcie_priv->pcie_irq_uf_count = 0;
	pcie_priv->tx_reclaim_done = 0;
	pcie_priv->tx_reclaim_req = 0;

	tasklet_init(&pcie_priv->reclaim_tq, qtnf_reclaim_tasklet_fn,
		     (unsigned long)pcie_priv);

	init_dummy_netdev(&bus->mux_dev);
	netif_napi_add(&bus->mux_dev, &bus->mux_napi,
		       qtnf_rx_poll, 10);

	pcie_priv->workqueue = create_singlethread_workqueue("QTNF_PEARL_PCIE");
	if (!pcie_priv->workqueue) {
		pr_err("failed to alloc bus workqueue\n");
		ret = -ENODEV;
		goto err_init;
	}

	if (!pci_is_pcie(pdev)) {
		pr_err("device %s is not PCI Express\n", pci_name(pdev));
		ret = -EIO;
		goto err_base;
	}

	qtnf_tune_pcie_mps(pcie_priv);

	ret = pcim_enable_device(pdev);
	if (ret) {
		pr_err("failed to init PCI device %x\n", pdev->device);
		goto err_base;
	} else {
		pr_debug("successful init of PCI device %x\n", pdev->device);
	}

#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
#else
	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
#endif
	if (ret) {
		pr_err("PCIE DMA coherent mask init failed\n");
		goto err_base;
	}

	pci_set_master(pdev);
	qtnf_pcie_init_irq(pcie_priv);

	ret = qtnf_pcie_init_memory(pcie_priv);
	if (ret < 0) {
		pr_err("PCIE memory init failed\n");
		goto err_base;
	}

	pci_save_state(pdev);

	ret = qtnf_pcie_init_shm_ipc(pcie_priv);
	if (ret < 0) {
		pr_err("PCIE SHM IPC init failed\n");
		goto err_base;
	}

	ret = qtnf_pcie_init_xfer(pcie_priv);
	if (ret) {
		pr_err("PCIE xfer init failed\n");
		goto err_ipc;
	}

	/* init default irq settings */
	qtnf_init_hdp_irqs(pcie_priv);

	/* start with disabled irqs */
	qtnf_disable_hdp_irqs(pcie_priv);

	ret = devm_request_irq(&pdev->dev, pdev->irq, &qtnf_interrupt, 0,
			       "qtnf_pcie_irq", (void *)bus);
	if (ret) {
		pr_err("failed to request pcie irq %d\n", pdev->irq);
		goto err_xfer;
	}

	qtnf_bringup_fw_async(bus);

	return 0;

err_xfer:
	qtnf_free_xfer_buffers(pcie_priv);

err_ipc:
	qtnf_pcie_free_shm_ipc(pcie_priv);

err_base:
	flush_workqueue(pcie_priv->workqueue);
	destroy_workqueue(pcie_priv->workqueue);
	netif_napi_del(&bus->mux_napi);

err_init:
	tasklet_kill(&pcie_priv->reclaim_tq);
	pci_set_drvdata(pdev, NULL);

	return ret;
}