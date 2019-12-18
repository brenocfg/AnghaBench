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
struct xdp_sock {scalar_t__ state; struct net_device* dev; int /*<<< orphan*/  umem; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XSK_BOUND ; 
 int /*<<< orphan*/  XSK_UNBOUND ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 int /*<<< orphan*/  xdp_del_sk_umem (int /*<<< orphan*/ ,struct xdp_sock*) ; 

__attribute__((used)) static void xsk_unbind_dev(struct xdp_sock *xs)
{
	struct net_device *dev = xs->dev;

	if (xs->state != XSK_BOUND)
		return;
	WRITE_ONCE(xs->state, XSK_UNBOUND);

	/* Wait for driver to stop using the xdp socket. */
	xdp_del_sk_umem(xs->umem, xs);
	xs->dev = NULL;
	synchronize_net();
	dev_put(dev);
}