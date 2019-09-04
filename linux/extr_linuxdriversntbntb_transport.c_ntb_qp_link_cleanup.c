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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ntb_transport_qp {int /*<<< orphan*/  link_is_up; int /*<<< orphan*/  cb_data; int /*<<< orphan*/  (* event_handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  link_work; int /*<<< orphan*/  qp_num; struct ntb_transport_ctx* transport; } ;
struct ntb_transport_ctx {TYPE_1__* ndev; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_qp_link_down_reset (struct ntb_transport_qp*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ntb_qp_link_cleanup(struct ntb_transport_qp *qp)
{
	struct ntb_transport_ctx *nt = qp->transport;
	struct pci_dev *pdev = nt->ndev->pdev;

	dev_info(&pdev->dev, "qp %d: Link Cleanup\n", qp->qp_num);

	cancel_delayed_work_sync(&qp->link_work);
	ntb_qp_link_down_reset(qp);

	if (qp->event_handler)
		qp->event_handler(qp->cb_data, qp->link_is_up);
}