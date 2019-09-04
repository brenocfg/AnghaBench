#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfrm_type {int (* get_mtu ) (struct xfrm_state*,int) ;} ;
struct TYPE_4__ {int header_len; } ;
struct TYPE_3__ {scalar_t__ state; } ;
struct xfrm_state {TYPE_2__ props; TYPE_1__ km; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 struct xfrm_type* READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ XFRM_STATE_VALID ; 
 int stub1 (struct xfrm_state*,int) ; 

int xfrm_state_mtu(struct xfrm_state *x, int mtu)
{
	const struct xfrm_type *type = READ_ONCE(x->type);

	if (x->km.state == XFRM_STATE_VALID &&
	    type && type->get_mtu)
		return type->get_mtu(x, mtu);

	return mtu - x->props.header_len;
}