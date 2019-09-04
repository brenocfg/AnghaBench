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
struct rocker {int /*<<< orphan*/  cmd_ring; int /*<<< orphan*/  event_ring; int /*<<< orphan*/  cmd_ring_lock; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  ROCKER_DMA_CMD ; 
 int /*<<< orphan*/  ROCKER_DMA_CMD_DEFAULT_SIZE ; 
 int /*<<< orphan*/  ROCKER_DMA_EVENT ; 
 int /*<<< orphan*/  ROCKER_DMA_EVENT_DEFAULT_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int rocker_dma_cmd_ring_waits_alloc (struct rocker*) ; 
 int /*<<< orphan*/  rocker_dma_cmd_ring_waits_free (struct rocker*) ; 
 int rocker_dma_ring_bufs_alloc (struct rocker*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rocker_dma_ring_bufs_free (struct rocker*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rocker_dma_ring_create (struct rocker*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rocker_dma_ring_destroy (struct rocker*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rocker_dma_ring_pass_to_producer (struct rocker*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rocker_dma_rings_init(struct rocker *rocker)
{
	const struct pci_dev *pdev = rocker->pdev;
	int err;

	err = rocker_dma_ring_create(rocker, ROCKER_DMA_CMD,
				     ROCKER_DMA_CMD_DEFAULT_SIZE,
				     &rocker->cmd_ring);
	if (err) {
		dev_err(&pdev->dev, "failed to create command dma ring\n");
		return err;
	}

	spin_lock_init(&rocker->cmd_ring_lock);

	err = rocker_dma_ring_bufs_alloc(rocker, &rocker->cmd_ring,
					 PCI_DMA_BIDIRECTIONAL, PAGE_SIZE);
	if (err) {
		dev_err(&pdev->dev, "failed to alloc command dma ring buffers\n");
		goto err_dma_cmd_ring_bufs_alloc;
	}

	err = rocker_dma_cmd_ring_waits_alloc(rocker);
	if (err) {
		dev_err(&pdev->dev, "failed to alloc command dma ring waits\n");
		goto err_dma_cmd_ring_waits_alloc;
	}

	err = rocker_dma_ring_create(rocker, ROCKER_DMA_EVENT,
				     ROCKER_DMA_EVENT_DEFAULT_SIZE,
				     &rocker->event_ring);
	if (err) {
		dev_err(&pdev->dev, "failed to create event dma ring\n");
		goto err_dma_event_ring_create;
	}

	err = rocker_dma_ring_bufs_alloc(rocker, &rocker->event_ring,
					 PCI_DMA_FROMDEVICE, PAGE_SIZE);
	if (err) {
		dev_err(&pdev->dev, "failed to alloc event dma ring buffers\n");
		goto err_dma_event_ring_bufs_alloc;
	}
	rocker_dma_ring_pass_to_producer(rocker, &rocker->event_ring);
	return 0;

err_dma_event_ring_bufs_alloc:
	rocker_dma_ring_destroy(rocker, &rocker->event_ring);
err_dma_event_ring_create:
	rocker_dma_ring_bufs_free(rocker, &rocker->cmd_ring,
				  PCI_DMA_BIDIRECTIONAL);
err_dma_cmd_ring_waits_alloc:
	rocker_dma_cmd_ring_waits_free(rocker);
err_dma_cmd_ring_bufs_alloc:
	rocker_dma_ring_destroy(rocker, &rocker->cmd_ring);
	return err;
}