#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct xfrm_mode {int flags; } ;
struct TYPE_10__ {int family; int /*<<< orphan*/  mode; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  proto; } ;
struct TYPE_8__ {int family; } ;
struct xfrm_state {struct xfrm_mode outer_mode; TYPE_4__ props; TYPE_6__* type; TYPE_3__ id; int /*<<< orphan*/  type_offload; struct xfrm_mode inner_mode_iaf; struct xfrm_mode inner_mode; TYPE_2__ sel; } ;
struct TYPE_12__ {int (* init_state ) (struct xfrm_state*) ;} ;
struct TYPE_7__ {scalar_t__ sysctl_ip_no_pmtu_disc; } ;
struct TYPE_11__ {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int AF_UNSPEC ; 
 int EPROTONOSUPPORT ; 
 int XFRM_MODE_FLAG_TUNNEL ; 
 int /*<<< orphan*/  XFRM_STATE_NOPMTUDISC ; 
 int stub1 (struct xfrm_state*) ; 
 struct xfrm_mode* xfrm_get_mode (int /*<<< orphan*/ ,int) ; 
 TYPE_6__* xfrm_get_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfrm_get_type_offload (int /*<<< orphan*/ ,int,int) ; 
 int xfrm_init_replay (struct xfrm_state*) ; 
 TYPE_5__* xs_net (struct xfrm_state*) ; 

int __xfrm_init_state(struct xfrm_state *x, bool init_replay, bool offload)
{
	const struct xfrm_mode *inner_mode;
	const struct xfrm_mode *outer_mode;
	int family = x->props.family;
	int err;

	if (family == AF_INET &&
	    xs_net(x)->ipv4.sysctl_ip_no_pmtu_disc)
		x->props.flags |= XFRM_STATE_NOPMTUDISC;

	err = -EPROTONOSUPPORT;

	if (x->sel.family != AF_UNSPEC) {
		inner_mode = xfrm_get_mode(x->props.mode, x->sel.family);
		if (inner_mode == NULL)
			goto error;

		if (!(inner_mode->flags & XFRM_MODE_FLAG_TUNNEL) &&
		    family != x->sel.family)
			goto error;

		x->inner_mode = *inner_mode;
	} else {
		const struct xfrm_mode *inner_mode_iaf;
		int iafamily = AF_INET;

		inner_mode = xfrm_get_mode(x->props.mode, x->props.family);
		if (inner_mode == NULL)
			goto error;

		if (!(inner_mode->flags & XFRM_MODE_FLAG_TUNNEL))
			goto error;

		x->inner_mode = *inner_mode;

		if (x->props.family == AF_INET)
			iafamily = AF_INET6;

		inner_mode_iaf = xfrm_get_mode(x->props.mode, iafamily);
		if (inner_mode_iaf) {
			if (inner_mode_iaf->flags & XFRM_MODE_FLAG_TUNNEL)
				x->inner_mode_iaf = *inner_mode_iaf;
		}
	}

	x->type = xfrm_get_type(x->id.proto, family);
	if (x->type == NULL)
		goto error;

	x->type_offload = xfrm_get_type_offload(x->id.proto, family, offload);

	err = x->type->init_state(x);
	if (err)
		goto error;

	outer_mode = xfrm_get_mode(x->props.mode, family);
	if (!outer_mode) {
		err = -EPROTONOSUPPORT;
		goto error;
	}

	x->outer_mode = *outer_mode;
	if (init_replay) {
		err = xfrm_init_replay(x);
		if (err)
			goto error;
	}

error:
	return err;
}