#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uwb_rsv {int state; int ie_valid; int /*<<< orphan*/  rc; } ;
typedef  enum uwb_rsv_state { ____Placeholder_uwb_rsv_state } uwb_rsv_state ;

/* Variables and functions */
 int /*<<< orphan*/  uwb_rsv_dump (char*,struct uwb_rsv*) ; 
 int /*<<< orphan*/  uwb_rsv_sched_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_rsv_stroke_timer (struct uwb_rsv*) ; 

__attribute__((used)) static void uwb_rsv_state_update(struct uwb_rsv *rsv,
				 enum uwb_rsv_state new_state)
{
	rsv->state = new_state;
	rsv->ie_valid = false;

	uwb_rsv_dump("SU", rsv);

	uwb_rsv_stroke_timer(rsv);
	uwb_rsv_sched_update(rsv->rc);
}