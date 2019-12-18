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
struct xfrmi_net {int dummy; } ;
struct xfrm_if_parms {int dummy; } ;
struct xfrm_if {int /*<<< orphan*/  dev; struct net* net; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct xfrmi_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_state_change (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 int xfrmi_change (struct xfrm_if*,struct xfrm_if_parms*) ; 
 int /*<<< orphan*/  xfrmi_link (struct xfrmi_net*,struct xfrm_if*) ; 
 int /*<<< orphan*/  xfrmi_net_id ; 
 int /*<<< orphan*/  xfrmi_unlink (struct xfrmi_net*,struct xfrm_if*) ; 

__attribute__((used)) static int xfrmi_update(struct xfrm_if *xi, struct xfrm_if_parms *p)
{
	struct net *net = xi->net;
	struct xfrmi_net *xfrmn = net_generic(net, xfrmi_net_id);
	int err;

	xfrmi_unlink(xfrmn, xi);
	synchronize_net();
	err = xfrmi_change(xi, p);
	xfrmi_link(xfrmn, xi);
	netdev_state_change(xi->dev);
	return err;
}