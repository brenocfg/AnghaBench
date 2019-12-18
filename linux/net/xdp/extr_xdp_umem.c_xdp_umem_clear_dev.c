#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct xdp_umem {int zc; TYPE_3__* dev; int /*<<< orphan*/  queue_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue_id; int /*<<< orphan*/ * umem; } ;
struct netdev_bpf {TYPE_1__ xsk; int /*<<< orphan*/  command; } ;
struct TYPE_8__ {TYPE_2__* netdev_ops; } ;
struct TYPE_7__ {int (* ndo_bpf ) (TYPE_3__*,struct netdev_bpf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  XDP_SETUP_XSK_UMEM ; 
 int /*<<< orphan*/  dev_put (TYPE_3__*) ; 
 int stub1 (TYPE_3__*,struct netdev_bpf*) ; 
 int /*<<< orphan*/  xdp_clear_umem_at_qid (TYPE_3__*,int /*<<< orphan*/ ) ; 

void xdp_umem_clear_dev(struct xdp_umem *umem)
{
	struct netdev_bpf bpf;
	int err;

	ASSERT_RTNL();

	if (!umem->dev)
		return;

	if (umem->zc) {
		bpf.command = XDP_SETUP_XSK_UMEM;
		bpf.xsk.umem = NULL;
		bpf.xsk.queue_id = umem->queue_id;

		err = umem->dev->netdev_ops->ndo_bpf(umem->dev, &bpf);

		if (err)
			WARN(1, "failed to disable umem!\n");
	}

	xdp_clear_umem_at_qid(umem->dev, umem->queue_id);

	dev_put(umem->dev);
	umem->dev = NULL;
	umem->zc = false;
}