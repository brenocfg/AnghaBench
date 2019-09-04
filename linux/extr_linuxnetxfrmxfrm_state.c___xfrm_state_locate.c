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
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  daddr; int /*<<< orphan*/  spi; } ;
struct TYPE_4__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_6__ {int v; int m; } ;
struct xfrm_state {TYPE_2__ id; TYPE_1__ props; TYPE_3__ mark; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct xfrm_state* __xfrm_state_lookup (struct net*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct xfrm_state* __xfrm_state_lookup_byaddr (struct net*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static inline struct xfrm_state *
__xfrm_state_locate(struct xfrm_state *x, int use_spi, int family)
{
	struct net *net = xs_net(x);
	u32 mark = x->mark.v & x->mark.m;

	if (use_spi)
		return __xfrm_state_lookup(net, mark, &x->id.daddr,
					   x->id.spi, x->id.proto, family);
	else
		return __xfrm_state_lookup_byaddr(net, mark,
						  &x->id.daddr,
						  &x->props.saddr,
						  x->id.proto, family);
}