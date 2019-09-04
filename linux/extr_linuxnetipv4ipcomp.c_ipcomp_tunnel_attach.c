#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  a4; } ;
struct TYPE_9__ {TYPE_3__ saddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  a4; } ;
struct TYPE_7__ {TYPE_1__ daddr; } ;
struct TYPE_10__ {int v; int m; } ;
struct xfrm_state {int /*<<< orphan*/  tunnel_users; struct xfrm_state* tunnel; TYPE_4__ props; TYPE_2__ id; TYPE_5__ mark; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPPROTO_IPIP ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct xfrm_state* ipcomp_tunnel_create (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_state_hold (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_state_insert (struct xfrm_state*) ; 
 struct xfrm_state* xfrm_state_lookup (struct net*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int ipcomp_tunnel_attach(struct xfrm_state *x)
{
	struct net *net = xs_net(x);
	int err = 0;
	struct xfrm_state *t;
	u32 mark = x->mark.v & x->mark.m;

	t = xfrm_state_lookup(net, mark, (xfrm_address_t *)&x->id.daddr.a4,
			      x->props.saddr.a4, IPPROTO_IPIP, AF_INET);
	if (!t) {
		t = ipcomp_tunnel_create(x);
		if (!t) {
			err = -EINVAL;
			goto out;
		}
		xfrm_state_insert(t);
		xfrm_state_hold(t);
	}
	x->tunnel = t;
	atomic_inc(&t->tunnel_users);
out:
	return err;
}