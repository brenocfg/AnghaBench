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
typedef  int /*<<< orphan*/  xfrm_address_t ;
struct TYPE_2__ {int /*<<< orphan*/  saddr; } ;
struct xfrm_state {TYPE_1__ props; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfrm6_tunnel_free_spi (struct net*,int /*<<< orphan*/ *) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static void xfrm6_tunnel_destroy(struct xfrm_state *x)
{
	struct net *net = xs_net(x);

	xfrm6_tunnel_free_spi(net, (xfrm_address_t *)&x->props.saddr);
}