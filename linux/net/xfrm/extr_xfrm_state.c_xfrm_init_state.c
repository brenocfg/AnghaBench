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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct xfrm_state {TYPE_1__ km; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFRM_STATE_VALID ; 
 int __xfrm_init_state (struct xfrm_state*,int,int) ; 

int xfrm_init_state(struct xfrm_state *x)
{
	int err;

	err = __xfrm_init_state(x, true, false);
	if (!err)
		x->km.state = XFRM_STATE_VALID;

	return err;
}