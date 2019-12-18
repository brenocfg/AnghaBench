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
struct TYPE_3__ {scalar_t__ state; } ;
struct xfrm_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  xflags; TYPE_2__* repl; TYPE_1__ km; } ;
struct timer_list {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* notify ) (struct xfrm_state*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XFRM_REPLAY_TIMEOUT ; 
 scalar_t__ XFRM_STATE_VALID ; 
 int /*<<< orphan*/  XFRM_TIME_DEFER ; 
 struct xfrm_state* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtimer ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct xfrm_state*,int /*<<< orphan*/ ) ; 
 struct xfrm_state* x ; 
 scalar_t__ xfrm_aevent_is_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_net (struct xfrm_state*) ; 

__attribute__((used)) static void xfrm_replay_timer_handler(struct timer_list *t)
{
	struct xfrm_state *x = from_timer(x, t, rtimer);

	spin_lock(&x->lock);

	if (x->km.state == XFRM_STATE_VALID) {
		if (xfrm_aevent_is_on(xs_net(x)))
			x->repl->notify(x, XFRM_REPLAY_TIMEOUT);
		else
			x->xflags |= XFRM_TIME_DEFER;
	}

	spin_unlock(&x->lock);
}