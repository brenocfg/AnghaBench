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
struct TYPE_10__ {int /*<<< orphan*/  state; } ;
struct TYPE_8__ {int /*<<< orphan*/ * a6; } ;
struct TYPE_9__ {TYPE_3__ saddr; int /*<<< orphan*/  mode; int /*<<< orphan*/  family; } ;
struct TYPE_6__ {int /*<<< orphan*/ * a6; } ;
struct TYPE_7__ {TYPE_1__ daddr; int /*<<< orphan*/  spi; int /*<<< orphan*/  proto; } ;
struct xfrm_state {TYPE_5__ km; int /*<<< orphan*/  tunnel_users; int /*<<< orphan*/  mark; TYPE_4__ props; int /*<<< orphan*/  sel; TYPE_2__ id; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  XFRM_STATE_DEAD ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xfrm6_tunnel_alloc_spi (struct net*,int /*<<< orphan*/ *) ; 
 scalar_t__ xfrm_init_state (struct xfrm_state*) ; 
 struct xfrm_state* xfrm_state_alloc (struct net*) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static struct xfrm_state *ipcomp6_tunnel_create(struct xfrm_state *x)
{
	struct net *net = xs_net(x);
	struct xfrm_state *t = NULL;

	t = xfrm_state_alloc(net);
	if (!t)
		goto out;

	t->id.proto = IPPROTO_IPV6;
	t->id.spi = xfrm6_tunnel_alloc_spi(net, (xfrm_address_t *)&x->props.saddr);
	if (!t->id.spi)
		goto error;

	memcpy(t->id.daddr.a6, x->id.daddr.a6, sizeof(struct in6_addr));
	memcpy(&t->sel, &x->sel, sizeof(t->sel));
	t->props.family = AF_INET6;
	t->props.mode = x->props.mode;
	memcpy(t->props.saddr.a6, x->props.saddr.a6, sizeof(struct in6_addr));
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