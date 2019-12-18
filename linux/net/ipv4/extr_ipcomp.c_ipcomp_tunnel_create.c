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
struct TYPE_10__ {int /*<<< orphan*/  state; } ;
struct TYPE_8__ {int /*<<< orphan*/  a4; } ;
struct TYPE_9__ {int /*<<< orphan*/  extra_flags; int /*<<< orphan*/  flags; TYPE_3__ saddr; int /*<<< orphan*/  mode; int /*<<< orphan*/  family; } ;
struct TYPE_6__ {int /*<<< orphan*/  a4; } ;
struct TYPE_7__ {TYPE_1__ daddr; int /*<<< orphan*/  spi; int /*<<< orphan*/  proto; } ;
struct xfrm_state {TYPE_5__ km; int /*<<< orphan*/  tunnel_users; int /*<<< orphan*/  mark; TYPE_4__ props; int /*<<< orphan*/  sel; TYPE_2__ id; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IPPROTO_IPIP ; 
 int /*<<< orphan*/  XFRM_STATE_DEAD ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ xfrm_init_state (struct xfrm_state*) ; 
 struct xfrm_state* xfrm_state_alloc (struct net*) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static struct xfrm_state *ipcomp_tunnel_create(struct xfrm_state *x)
{
	struct net *net = xs_net(x);
	struct xfrm_state *t;

	t = xfrm_state_alloc(net);
	if (!t)
		goto out;

	t->id.proto = IPPROTO_IPIP;
	t->id.spi = x->props.saddr.a4;
	t->id.daddr.a4 = x->id.daddr.a4;
	memcpy(&t->sel, &x->sel, sizeof(t->sel));
	t->props.family = AF_INET;
	t->props.mode = x->props.mode;
	t->props.saddr.a4 = x->props.saddr.a4;
	t->props.flags = x->props.flags;
	t->props.extra_flags = x->props.extra_flags;
	memcpy(&t->mark, &x->mark, sizeof(t->mark));

	if (xfrm_init_state(t))
		goto error;

	atomic_set(&t->tunnel_users, 1);
out:
	return t;

error:
	t->km.state = XFRM_STATE_DEAD;
	xfrm_state_put(t);
	t = NULL;
	goto out;
}