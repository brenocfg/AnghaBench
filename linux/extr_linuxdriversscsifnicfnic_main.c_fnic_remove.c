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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct fnic {int stop_rx_link_events; int in_remove; int /*<<< orphan*/  vdev; struct fc_lport* lport; int /*<<< orphan*/  list; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  frame_queue; int /*<<< orphan*/  ctlr; int /*<<< orphan*/  fnic_lock; int /*<<< orphan*/  fip_frame_queue; int /*<<< orphan*/  fip_timer; TYPE_1__ config; int /*<<< orphan*/  notify_timer; } ;
struct fc_lport {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int VFCF_FIP_CAPABLE ; 
 scalar_t__ VNIC_DEV_INTR_MODE_MSI ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_exch_mgr_free (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_fabric_logoff (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_destroy (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcoe_ctlr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnic_cleanup (struct fnic*) ; 
 int /*<<< orphan*/  fnic_clear_intr_mode (struct fnic*) ; 
 int /*<<< orphan*/  fnic_event_queue ; 
 int /*<<< orphan*/  fnic_fcoe_evlist_free (struct fnic*) ; 
 int /*<<< orphan*/  fnic_fcoe_reset_vlans (struct fnic*) ; 
 int /*<<< orphan*/  fnic_free_intr (struct fnic*) ; 
 int /*<<< orphan*/  fnic_free_vnic_resources (struct fnic*) ; 
 int /*<<< orphan*/  fnic_iounmap (struct fnic*) ; 
 int /*<<< orphan*/  fnic_list_lock ; 
 int /*<<< orphan*/  fnic_stats_debugfs_remove (struct fnic*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct fnic* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vnic_dev_close (int /*<<< orphan*/ ) ; 
 scalar_t__ vnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_dev_notify_unset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_dev_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fnic_remove(struct pci_dev *pdev)
{
	struct fnic *fnic = pci_get_drvdata(pdev);
	struct fc_lport *lp = fnic->lport;
	unsigned long flags;

	/*
	 * Mark state so that the workqueue thread stops forwarding
	 * received frames and link events to the local port. ISR and
	 * other threads that can queue work items will also stop
	 * creating work items on the fnic workqueue
	 */
	spin_lock_irqsave(&fnic->fnic_lock, flags);
	fnic->stop_rx_link_events = 1;
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	if (vnic_dev_get_intr_mode(fnic->vdev) == VNIC_DEV_INTR_MODE_MSI)
		del_timer_sync(&fnic->notify_timer);

	/*
	 * Flush the fnic event queue. After this call, there should
	 * be no event queued for this fnic device in the workqueue
	 */
	flush_workqueue(fnic_event_queue);
	skb_queue_purge(&fnic->frame_queue);
	skb_queue_purge(&fnic->tx_queue);

	if (fnic->config.flags & VFCF_FIP_CAPABLE) {
		del_timer_sync(&fnic->fip_timer);
		skb_queue_purge(&fnic->fip_frame_queue);
		fnic_fcoe_reset_vlans(fnic);
		fnic_fcoe_evlist_free(fnic);
	}

	/*
	 * Log off the fabric. This stops all remote ports, dns port,
	 * logs off the fabric. This flushes all rport, disc, lport work
	 * before returning
	 */
	fc_fabric_logoff(fnic->lport);

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	fnic->in_remove = 1;
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	fcoe_ctlr_destroy(&fnic->ctlr);
	fc_lport_destroy(lp);
	fnic_stats_debugfs_remove(fnic);

	/*
	 * This stops the fnic device, masks all interrupts. Completed
	 * CQ entries are drained. Posted WQ/RQ/Copy-WQ entries are
	 * cleaned up
	 */
	fnic_cleanup(fnic);

	BUG_ON(!skb_queue_empty(&fnic->frame_queue));
	BUG_ON(!skb_queue_empty(&fnic->tx_queue));

	spin_lock_irqsave(&fnic_list_lock, flags);
	list_del(&fnic->list);
	spin_unlock_irqrestore(&fnic_list_lock, flags);

	fc_remove_host(fnic->lport->host);
	scsi_remove_host(fnic->lport->host);
	fc_exch_mgr_free(fnic->lport);
	vnic_dev_notify_unset(fnic->vdev);
	fnic_free_intr(fnic);
	fnic_free_vnic_resources(fnic);
	fnic_clear_intr_mode(fnic);
	vnic_dev_close(fnic->vdev);
	vnic_dev_unregister(fnic->vdev);
	fnic_iounmap(fnic);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	scsi_host_put(lp->host);
}