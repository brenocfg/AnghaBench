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
struct vnic_wq {int /*<<< orphan*/ * ctrl; int /*<<< orphan*/ ** bufs; int /*<<< orphan*/  ring; struct vnic_dev* vdev; } ;
struct vnic_dev {int dummy; } ;

/* Variables and functions */
 unsigned int VNIC_WQ_BUF_BLKS_MAX ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_dev_free_desc_ring (struct vnic_dev*,int /*<<< orphan*/ *) ; 

void vnic_wq_free(struct vnic_wq *wq)
{
	struct vnic_dev *vdev;
	unsigned int i;

	vdev = wq->vdev;

	vnic_dev_free_desc_ring(vdev, &wq->ring);

	for (i = 0; i < VNIC_WQ_BUF_BLKS_MAX; i++) {
		kfree(wq->bufs[i]);
		wq->bufs[i] = NULL;
	}

	wq->ctrl = NULL;

}