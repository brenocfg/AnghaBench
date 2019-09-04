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
struct xdp_sock {int /*<<< orphan*/  queue_id; struct net_device* dev; } ;
struct sock {int dummy; } ;
struct net_device {TYPE_1__* netdev_ops; } ;
struct TYPE_2__ {int (* ndo_xsk_async_xmit ) (struct net_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct net_device*,int /*<<< orphan*/ ) ; 
 struct xdp_sock* xdp_sk (struct sock*) ; 

__attribute__((used)) static int xsk_zc_xmit(struct sock *sk)
{
	struct xdp_sock *xs = xdp_sk(sk);
	struct net_device *dev = xs->dev;

	return dev->netdev_ops->ndo_xsk_async_xmit(dev, xs->queue_id);
}