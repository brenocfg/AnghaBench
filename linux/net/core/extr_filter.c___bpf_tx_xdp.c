#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct xdp_frame {int dummy; } ;
struct xdp_buff {scalar_t__ data; scalar_t__ data_end; } ;
struct net_device {TYPE_1__* netdev_ops; } ;
struct bpf_map {int dummy; } ;
struct TYPE_2__ {int (* ndo_xdp_xmit ) (struct net_device*,int,struct xdp_frame**,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  XDP_XMIT_FLUSH ; 
 struct xdp_frame* convert_to_xdp_frame (struct xdp_buff*) ; 
 int stub1 (struct net_device*,int,struct xdp_frame**,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int xdp_ok_fwd_dev (struct net_device*,scalar_t__) ; 

__attribute__((used)) static int __bpf_tx_xdp(struct net_device *dev,
			struct bpf_map *map,
			struct xdp_buff *xdp,
			u32 index)
{
	struct xdp_frame *xdpf;
	int err, sent;

	if (!dev->netdev_ops->ndo_xdp_xmit) {
		return -EOPNOTSUPP;
	}

	err = xdp_ok_fwd_dev(dev, xdp->data_end - xdp->data);
	if (unlikely(err))
		return err;

	xdpf = convert_to_xdp_frame(xdp);
	if (unlikely(!xdpf))
		return -EOVERFLOW;

	sent = dev->netdev_ops->ndo_xdp_xmit(dev, 1, &xdpf, XDP_XMIT_FLUSH);
	if (sent <= 0)
		return sent;
	return 0;
}