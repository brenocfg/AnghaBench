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
struct pci_dev {int dummy; } ;
struct nvme_queue {int /*<<< orphan*/  qid; int /*<<< orphan*/  cq_vector; TYPE_2__* dev; } ;
struct TYPE_3__ {int instance; } ;
struct TYPE_4__ {TYPE_1__ ctrl; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/ * nvme_irq ; 
 int /*<<< orphan*/ * nvme_irq_check ; 
 int pci_request_irq (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvme_queue*,char*,int,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ use_threaded_interrupts ; 

__attribute__((used)) static int queue_request_irq(struct nvme_queue *nvmeq)
{
	struct pci_dev *pdev = to_pci_dev(nvmeq->dev->dev);
	int nr = nvmeq->dev->ctrl.instance;

	if (use_threaded_interrupts) {
		return pci_request_irq(pdev, nvmeq->cq_vector, nvme_irq_check,
				nvme_irq, nvmeq, "nvme%dq%d", nr, nvmeq->qid);
	} else {
		return pci_request_irq(pdev, nvmeq->cq_vector, nvme_irq,
				NULL, nvmeq, "nvme%dq%d", nr, nvmeq->qid);
	}
}