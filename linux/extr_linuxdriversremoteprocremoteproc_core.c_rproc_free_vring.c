#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rproc_vring {TYPE_2__* rvdev; int /*<<< orphan*/  notifyid; int /*<<< orphan*/  dma; int /*<<< orphan*/  va; int /*<<< orphan*/  align; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct rproc {scalar_t__ table_ptr; int /*<<< orphan*/  notifyids; TYPE_1__ dev; } ;
struct fw_rsc_vdev {TYPE_3__* vring; } ;
struct TYPE_6__ {int notifyid; scalar_t__ da; } ;
struct TYPE_5__ {int rsc_offset; struct rproc_vring* vring; struct rproc* rproc; } ;

/* Variables and functions */
 int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rproc_free_vring(struct rproc_vring *rvring)
{
	int size = PAGE_ALIGN(vring_size(rvring->len, rvring->align));
	struct rproc *rproc = rvring->rvdev->rproc;
	int idx = rvring->rvdev->vring - rvring;
	struct fw_rsc_vdev *rsc;

	dma_free_coherent(rproc->dev.parent, size, rvring->va, rvring->dma);
	idr_remove(&rproc->notifyids, rvring->notifyid);

	/* reset resource entry info */
	rsc = (void *)rproc->table_ptr + rvring->rvdev->rsc_offset;
	rsc->vring[idx].da = 0;
	rsc->vring[idx].notifyid = -1;
}