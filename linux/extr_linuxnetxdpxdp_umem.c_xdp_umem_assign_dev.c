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
typedef  void* u32 ;
typedef  int u16 ;
struct xdp_umem {int zc; void* queue_id; struct net_device* dev; } ;
struct TYPE_3__ {void* queue_id; struct xdp_umem* umem; } ;
struct netdev_bpf {TYPE_1__ xsk; int /*<<< orphan*/  command; } ;
struct net_device {TYPE_2__* netdev_ops; } ;
struct TYPE_4__ {int (* ndo_bpf ) (struct net_device*,struct netdev_bpf*) ;int /*<<< orphan*/  ndo_xsk_async_xmit; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int XDP_COPY ; 
 int /*<<< orphan*/  XDP_QUERY_XSK_UMEM ; 
 int /*<<< orphan*/  XDP_SETUP_XSK_UMEM ; 
 int XDP_ZEROCOPY ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int stub1 (struct net_device*,struct netdev_bpf*) ; 
 int xdp_umem_query (struct net_device*,void*) ; 

int xdp_umem_assign_dev(struct xdp_umem *umem, struct net_device *dev,
			u32 queue_id, u16 flags)
{
	bool force_zc, force_copy;
	struct netdev_bpf bpf;
	int err;

	force_zc = flags & XDP_ZEROCOPY;
	force_copy = flags & XDP_COPY;

	if (force_zc && force_copy)
		return -EINVAL;

	if (force_copy)
		return 0;

	if (!dev->netdev_ops->ndo_bpf || !dev->netdev_ops->ndo_xsk_async_xmit)
		return force_zc ? -EOPNOTSUPP : 0; /* fail or fallback */

	bpf.command = XDP_QUERY_XSK_UMEM;

	rtnl_lock();
	err = xdp_umem_query(dev, queue_id);
	if (err) {
		err = err < 0 ? -EOPNOTSUPP : -EBUSY;
		goto err_rtnl_unlock;
	}

	bpf.command = XDP_SETUP_XSK_UMEM;
	bpf.xsk.umem = umem;
	bpf.xsk.queue_id = queue_id;

	err = dev->netdev_ops->ndo_bpf(dev, &bpf);
	if (err)
		goto err_rtnl_unlock;
	rtnl_unlock();

	dev_hold(dev);
	umem->dev = dev;
	umem->queue_id = queue_id;
	umem->zc = true;
	return 0;

err_rtnl_unlock:
	rtnl_unlock();
	return force_zc ? err : 0; /* fail or fallback */
}