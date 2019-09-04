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
struct virtqueue {struct rproc_vring* priv; } ;
struct rproc_vring {int notifyid; TYPE_1__* rvdev; } ;
struct rproc {TYPE_2__* ops; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* kick ) (struct rproc*,int) ;} ;
struct TYPE_3__ {struct rproc* rproc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct rproc*,int) ; 

__attribute__((used)) static bool rproc_virtio_notify(struct virtqueue *vq)
{
	struct rproc_vring *rvring = vq->priv;
	struct rproc *rproc = rvring->rvdev->rproc;
	int notifyid = rvring->notifyid;

	dev_dbg(&rproc->dev, "kicking vq index: %d\n", notifyid);

	rproc->ops->kick(rproc, notifyid);
	return true;
}