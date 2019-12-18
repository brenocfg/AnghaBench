#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ state; scalar_t__ dying; } ;
struct TYPE_13__ {scalar_t__ v; scalar_t__ m; } ;
struct TYPE_14__ {TYPE_3__ smark; int /*<<< orphan*/  family; } ;
struct TYPE_12__ {scalar_t__ use_time; } ;
struct TYPE_17__ {scalar_t__ encap_type; } ;
struct TYPE_11__ {int /*<<< orphan*/  proto; } ;
struct xfrm_state {int /*<<< orphan*/  lock; TYPE_6__ km; scalar_t__ if_id; TYPE_4__ props; TYPE_2__ curlft; int /*<<< orphan*/  mtimer; TYPE_7__ lft; TYPE_7__ sel; TYPE_7__* coaddr; TYPE_7__* encap; TYPE_1__ id; } ;
struct TYPE_15__ {int /*<<< orphan*/  xfrm_state_lock; } ;
struct net {TYPE_5__ xfrm; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL_SOFT ; 
 int /*<<< orphan*/  IPSEC_PROTO_ANY ; 
 scalar_t__ XFRM_STATE_ACQ ; 
 scalar_t__ XFRM_STATE_DEAD ; 
 scalar_t__ XFRM_STATE_VALID ; 
 int /*<<< orphan*/  __xfrm_state_bump_genids (struct xfrm_state*) ; 
 int /*<<< orphan*/  __xfrm_state_insert (struct xfrm_state*) ; 
 struct xfrm_state* __xfrm_state_locate (struct xfrm_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __xfrm_state_put (struct xfrm_state*) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ memcmp (TYPE_7__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_7__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int xfrm_id_proto_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_state_check_expire (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_state_delete (struct xfrm_state*) ; 
 scalar_t__ xfrm_state_kern (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 
 struct net* xs_net (struct xfrm_state*) ; 

int xfrm_state_update(struct xfrm_state *x)
{
	struct xfrm_state *x1, *to_put;
	int err;
	int use_spi = xfrm_id_proto_match(x->id.proto, IPSEC_PROTO_ANY);
	struct net *net = xs_net(x);

	to_put = NULL;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	x1 = __xfrm_state_locate(x, use_spi, x->props.family);

	err = -ESRCH;
	if (!x1)
		goto out;

	if (xfrm_state_kern(x1)) {
		to_put = x1;
		err = -EEXIST;
		goto out;
	}

	if (x1->km.state == XFRM_STATE_ACQ) {
		__xfrm_state_insert(x);
		x = NULL;
	}
	err = 0;

out:
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);

	if (to_put)
		xfrm_state_put(to_put);

	if (err)
		return err;

	if (!x) {
		xfrm_state_delete(x1);
		xfrm_state_put(x1);
		return 0;
	}

	err = -EINVAL;
	spin_lock_bh(&x1->lock);
	if (likely(x1->km.state == XFRM_STATE_VALID)) {
		if (x->encap && x1->encap &&
		    x->encap->encap_type == x1->encap->encap_type)
			memcpy(x1->encap, x->encap, sizeof(*x1->encap));
		else if (x->encap || x1->encap)
			goto fail;

		if (x->coaddr && x1->coaddr) {
			memcpy(x1->coaddr, x->coaddr, sizeof(*x1->coaddr));
		}
		if (!use_spi && memcmp(&x1->sel, &x->sel, sizeof(x1->sel)))
			memcpy(&x1->sel, &x->sel, sizeof(x1->sel));
		memcpy(&x1->lft, &x->lft, sizeof(x1->lft));
		x1->km.dying = 0;

		hrtimer_start(&x1->mtimer, ktime_set(1, 0),
			      HRTIMER_MODE_REL_SOFT);
		if (x1->curlft.use_time)
			xfrm_state_check_expire(x1);

		if (x->props.smark.m || x->props.smark.v || x->if_id) {
			spin_lock_bh(&net->xfrm.xfrm_state_lock);

			if (x->props.smark.m || x->props.smark.v)
				x1->props.smark = x->props.smark;

			if (x->if_id)
				x1->if_id = x->if_id;

			__xfrm_state_bump_genids(x1);
			spin_unlock_bh(&net->xfrm.xfrm_state_lock);
		}

		err = 0;
		x->km.state = XFRM_STATE_DEAD;
		__xfrm_state_put(x);
	}

fail:
	spin_unlock_bh(&x1->lock);

	xfrm_state_put(x1);

	return err;
}