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
struct qtnf_pcie_bus_priv {int /*<<< orphan*/  reclaim_tq; int /*<<< orphan*/  workqueue; } ;
struct qtnf_bus {scalar_t__ fw_state; int /*<<< orphan*/  mux_napi; int /*<<< orphan*/  firmware_init_complete; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ QTNF_FW_STATE_ACTIVE ; 
 scalar_t__ QTNF_FW_STATE_EP_DEAD ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 struct qtnf_pcie_bus_priv* get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 struct qtnf_bus* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  qtnf_core_detach (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_debugfs_remove (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_free_xfer_buffers (struct qtnf_pcie_bus_priv*) ; 
 int /*<<< orphan*/  qtnf_pcie_free_shm_ipc (struct qtnf_pcie_bus_priv*) ; 
 int /*<<< orphan*/  qtnf_reset_card (struct qtnf_pcie_bus_priv*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qtnf_pcie_remove(struct pci_dev *pdev)
{
	struct qtnf_pcie_bus_priv *priv;
	struct qtnf_bus *bus;

	bus = pci_get_drvdata(pdev);
	if (!bus)
		return;

	wait_for_completion(&bus->firmware_init_complete);

	if (bus->fw_state == QTNF_FW_STATE_ACTIVE ||
	    bus->fw_state == QTNF_FW_STATE_EP_DEAD)
		qtnf_core_detach(bus);

	priv = get_bus_priv(bus);

	netif_napi_del(&bus->mux_napi);
	flush_workqueue(priv->workqueue);
	destroy_workqueue(priv->workqueue);
	tasklet_kill(&priv->reclaim_tq);

	qtnf_free_xfer_buffers(priv);
	qtnf_debugfs_remove(bus);

	qtnf_pcie_free_shm_ipc(priv);
	qtnf_reset_card(priv);
}