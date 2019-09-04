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
struct pci_dev {int dummy; } ;
struct nvme_queue {int cq_vector; int /*<<< orphan*/  q_db; } ;
struct nvme_dev {int cmbsz; int q_depth; int num_vecs; int /*<<< orphan*/  max_qid; int /*<<< orphan*/  dbs; scalar_t__ cmb; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  dev; struct nvme_queue* queues; } ;
struct nvme_command {int dummy; } ;
struct irq_affinity {int pre_vectors; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int NVME_CMBSZ_SQS ; 
 int PCI_IRQ_AFFINITY ; 
 int PCI_IRQ_ALL_TYPES ; 
 unsigned long db_bar_size (struct nvme_dev*,int) ; 
 int /*<<< orphan*/  max (int,int) ; 
 int num_possible_cpus () ; 
 int nvme_cmb_qdepth (struct nvme_dev*,int,int) ; 
 int nvme_create_io_queues (struct nvme_dev*) ; 
 int /*<<< orphan*/  nvme_release_cmb (struct nvme_dev*) ; 
 int nvme_remap_bar (struct nvme_dev*,unsigned long) ; 
 int nvme_set_queue_count (int /*<<< orphan*/ *,int*) ; 
 int pci_alloc_irq_vectors_affinity (struct pci_dev*,int,int,int,struct irq_affinity*) ; 
 int /*<<< orphan*/  pci_free_irq (struct pci_dev*,int /*<<< orphan*/ ,struct nvme_queue*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int queue_request_irq (struct nvme_queue*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_setup_io_queues(struct nvme_dev *dev)
{
	struct nvme_queue *adminq = &dev->queues[0];
	struct pci_dev *pdev = to_pci_dev(dev->dev);
	int result, nr_io_queues;
	unsigned long size;

	struct irq_affinity affd = {
		.pre_vectors = 1
	};

	nr_io_queues = num_possible_cpus();
	result = nvme_set_queue_count(&dev->ctrl, &nr_io_queues);
	if (result < 0)
		return result;

	if (nr_io_queues == 0)
		return 0;

	if (dev->cmb && (dev->cmbsz & NVME_CMBSZ_SQS)) {
		result = nvme_cmb_qdepth(dev, nr_io_queues,
				sizeof(struct nvme_command));
		if (result > 0)
			dev->q_depth = result;
		else
			nvme_release_cmb(dev);
	}

	do {
		size = db_bar_size(dev, nr_io_queues);
		result = nvme_remap_bar(dev, size);
		if (!result)
			break;
		if (!--nr_io_queues)
			return -ENOMEM;
	} while (1);
	adminq->q_db = dev->dbs;

	/* Deregister the admin queue's interrupt */
	pci_free_irq(pdev, 0, adminq);

	/*
	 * If we enable msix early due to not intx, disable it again before
	 * setting up the full range we need.
	 */
	pci_free_irq_vectors(pdev);
	result = pci_alloc_irq_vectors_affinity(pdev, 1, nr_io_queues + 1,
			PCI_IRQ_ALL_TYPES | PCI_IRQ_AFFINITY, &affd);
	if (result <= 0)
		return -EIO;
	dev->num_vecs = result;
	dev->max_qid = max(result - 1, 1);

	/*
	 * Should investigate if there's a performance win from allocating
	 * more queues than interrupt vectors; it might allow the submission
	 * path to scale better, even if the receive path is limited by the
	 * number of interrupts.
	 */

	result = queue_request_irq(adminq);
	if (result) {
		adminq->cq_vector = -1;
		return result;
	}
	return nvme_create_io_queues(dev);
}