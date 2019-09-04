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
struct vio_dev {int /*<<< orphan*/  unit_address; int /*<<< orphan*/  irq; } ;
struct ibmvfc_crq_queue {scalar_t__ msgs; int /*<<< orphan*/  msg_token; } ;
struct ibmvfc_host {int /*<<< orphan*/  dev; scalar_t__ logged_in; int /*<<< orphan*/  state; int /*<<< orphan*/  tasklet; struct ibmvfc_crq_queue crq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 long H_BUSY ; 
 int /*<<< orphan*/  H_FREE_CRQ ; 
 scalar_t__ H_IS_LONG_BUSY (long) ; 
 int /*<<< orphan*/  IBMVFC_NO_CRQ ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ibmvfc_host*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  ibmvfc_dbg (struct ibmvfc_host*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 long plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 struct vio_dev* to_vio_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibmvfc_release_crq_queue(struct ibmvfc_host *vhost)
{
	long rc = 0;
	struct vio_dev *vdev = to_vio_dev(vhost->dev);
	struct ibmvfc_crq_queue *crq = &vhost->crq;

	ibmvfc_dbg(vhost, "Releasing CRQ\n");
	free_irq(vdev->irq, vhost);
	tasklet_kill(&vhost->tasklet);
	do {
		if (rc)
			msleep(100);
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	} while (rc == H_BUSY || H_IS_LONG_BUSY(rc));

	vhost->state = IBMVFC_NO_CRQ;
	vhost->logged_in = 0;
	dma_unmap_single(vhost->dev, crq->msg_token, PAGE_SIZE, DMA_BIDIRECTIONAL);
	free_page((unsigned long)crq->msgs);
}