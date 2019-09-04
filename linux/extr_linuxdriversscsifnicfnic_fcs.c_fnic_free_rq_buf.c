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
struct vnic_rq_buf {struct fc_frame* os_buf; int /*<<< orphan*/  len; int /*<<< orphan*/  dma_addr; } ;
struct vnic_rq {int /*<<< orphan*/  vdev; } ;
struct fnic {int /*<<< orphan*/  pdev; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fp_skb (struct fc_frame*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fnic* vnic_dev_priv (int /*<<< orphan*/ ) ; 

void fnic_free_rq_buf(struct vnic_rq *rq, struct vnic_rq_buf *buf)
{
	struct fc_frame *fp = buf->os_buf;
	struct fnic *fnic = vnic_dev_priv(rq->vdev);

	pci_unmap_single(fnic->pdev, buf->dma_addr, buf->len,
			 PCI_DMA_FROMDEVICE);

	dev_kfree_skb(fp_skb(fp));
	buf->os_buf = NULL;
}