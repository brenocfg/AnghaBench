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
typedef  int u32 ;
struct TYPE_8__ {int family; int /*<<< orphan*/  saddr; int /*<<< orphan*/  reqid; int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {scalar_t__ proto; int /*<<< orphan*/  daddr; } ;
struct TYPE_10__ {int v; int m; } ;
struct TYPE_6__ {scalar_t__ seq; } ;
struct xfrm_state {TYPE_3__ props; TYPE_2__ id; int /*<<< orphan*/  if_id; TYPE_5__ mark; TYPE_1__ km; } ;
struct TYPE_9__ {int /*<<< orphan*/  xfrm_state_lock; } ;
struct net {TYPE_4__ xfrm; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  IPSEC_PROTO_ANY ; 
 struct xfrm_state* __find_acq_core (struct net*,TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct xfrm_state* __xfrm_find_acq_byseq (struct net*,int,scalar_t__) ; 
 int /*<<< orphan*/  __xfrm_state_bump_genids (struct xfrm_state*) ; 
 int /*<<< orphan*/  __xfrm_state_insert (struct xfrm_state*) ; 
 struct xfrm_state* __xfrm_state_locate (struct xfrm_state*,int,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int xfrm_id_proto_match (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_state_delete (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 
 struct net* xs_net (struct xfrm_state*) ; 

int xfrm_state_add(struct xfrm_state *x)
{
	struct net *net = xs_net(x);
	struct xfrm_state *x1, *to_put;
	int family;
	int err;
	u32 mark = x->mark.v & x->mark.m;
	int use_spi = xfrm_id_proto_match(x->id.proto, IPSEC_PROTO_ANY);

	family = x->props.family;

	to_put = NULL;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);

	x1 = __xfrm_state_locate(x, use_spi, family);
	if (x1) {
		to_put = x1;
		x1 = NULL;
		err = -EEXIST;
		goto out;
	}

	if (use_spi && x->km.seq) {
		x1 = __xfrm_find_acq_byseq(net, mark, x->km.seq);
		if (x1 && ((x1->id.proto != x->id.proto) ||
		    !xfrm_addr_equal(&x1->id.daddr, &x->id.daddr, family))) {
			to_put = x1;
			x1 = NULL;
		}
	}

	if (use_spi && !x1)
		x1 = __find_acq_core(net, &x->mark, family, x->props.mode,
				     x->props.reqid, x->if_id, x->id.proto,
				     &x->id.daddr, &x->props.saddr, 0);

	__xfrm_state_bump_genids(x);
	__xfrm_state_insert(x);
	err = 0;

out:
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);

	if (x1) {
		xfrm_state_delete(x1);
		xfrm_state_put(x1);
	}

	if (to_put)
		xfrm_state_put(to_put);

	return err;
}