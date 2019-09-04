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
struct xen_pci_op {int err; } ;
struct pcifront_device {unsigned int irq; int /*<<< orphan*/  sh_info_lock; TYPE_2__* xdev; TYPE_1__* sh_info; int /*<<< orphan*/  evtchn; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  evtchn_port_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; struct xen_pci_op op; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ NSEC_PER_SEC ; 
 int XEN_PCI_ERR_dev_not_found ; 
 int /*<<< orphan*/  _XEN_PCIB_active ; 
 int /*<<< orphan*/  _XEN_PCIF_active ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ jiffies ; 
 int ktime_get_ns () ; 
 int /*<<< orphan*/  memcpy (struct xen_pci_op*,struct xen_pci_op*,int) ; 
 int /*<<< orphan*/  notify_remote_via_evtchn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_pcifront_aer_op (struct pcifront_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  xen_clear_irq_pending (unsigned int) ; 
 int /*<<< orphan*/  xen_poll_irq_timeout (unsigned int,scalar_t__) ; 

__attribute__((used)) static int do_pci_op(struct pcifront_device *pdev, struct xen_pci_op *op)
{
	int err = 0;
	struct xen_pci_op *active_op = &pdev->sh_info->op;
	unsigned long irq_flags;
	evtchn_port_t port = pdev->evtchn;
	unsigned irq = pdev->irq;
	s64 ns, ns_timeout;

	spin_lock_irqsave(&pdev->sh_info_lock, irq_flags);

	memcpy(active_op, op, sizeof(struct xen_pci_op));

	/* Go */
	wmb();
	set_bit(_XEN_PCIF_active, (unsigned long *)&pdev->sh_info->flags);
	notify_remote_via_evtchn(port);

	/*
	 * We set a poll timeout of 3 seconds but give up on return after
	 * 2 seconds. It is better to time out too late rather than too early
	 * (in the latter case we end up continually re-executing poll() with a
	 * timeout in the past). 1s difference gives plenty of slack for error.
	 */
	ns_timeout = ktime_get_ns() + 2 * (s64)NSEC_PER_SEC;

	xen_clear_irq_pending(irq);

	while (test_bit(_XEN_PCIF_active,
			(unsigned long *)&pdev->sh_info->flags)) {
		xen_poll_irq_timeout(irq, jiffies + 3*HZ);
		xen_clear_irq_pending(irq);
		ns = ktime_get_ns();
		if (ns > ns_timeout) {
			dev_err(&pdev->xdev->dev,
				"pciback not responding!!!\n");
			clear_bit(_XEN_PCIF_active,
				  (unsigned long *)&pdev->sh_info->flags);
			err = XEN_PCI_ERR_dev_not_found;
			goto out;
		}
	}

	/*
	* We might lose backend service request since we
	* reuse same evtchn with pci_conf backend response. So re-schedule
	* aer pcifront service.
	*/
	if (test_bit(_XEN_PCIB_active,
			(unsigned long *)&pdev->sh_info->flags)) {
		dev_err(&pdev->xdev->dev,
			"schedule aer pcifront service\n");
		schedule_pcifront_aer_op(pdev);
	}

	memcpy(op, active_op, sizeof(struct xen_pci_op));

	err = op->err;
out:
	spin_unlock_irqrestore(&pdev->sh_info_lock, irq_flags);
	return err;
}