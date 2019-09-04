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
struct TYPE_4__ {int /*<<< orphan*/  bm; } ;
struct uwb_rsv_move {TYPE_2__ companion_mas; } ;
struct TYPE_3__ {int /*<<< orphan*/  bm; } ;
struct uwb_rsv {int needs_release_companion_mas; TYPE_1__ mas; struct uwb_rsv_move mv; struct uwb_rc* rc; } ;
struct uwb_drp_backoff_win {int can_reserve_extra_mases; } ;
struct uwb_rc {struct uwb_drp_backoff_win bow; } ;
struct uwb_mas_bm {int /*<<< orphan*/  bm; } ;
struct uwb_ie_drp {int dummy; } ;

/* Variables and functions */
#define  UWB_DRP_CONFLICT_ACT2 129 
#define  UWB_DRP_CONFLICT_ACT3 128 
 int /*<<< orphan*/  UWB_NUM_MAS ; 
 int /*<<< orphan*/  UWB_RSV_STATE_O_ESTABLISHED ; 
 int /*<<< orphan*/  UWB_RSV_STATE_O_MODIFIED ; 
 int /*<<< orphan*/  UWB_RSV_STATE_T_CONFLICT ; 
 int /*<<< orphan*/  UWB_RSV_STATE_T_EXPANDING_CONFLICT ; 
 int /*<<< orphan*/  bitmap_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int evaluate_conflict_action (struct uwb_ie_drp*,int,struct uwb_rsv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_drp_avail_release (struct uwb_rc*,TYPE_2__*) ; 
 int /*<<< orphan*/  uwb_rsv_backoff_win_increment (struct uwb_rc*) ; 
 scalar_t__ uwb_rsv_is_owner (struct uwb_rsv*) ; 
 int /*<<< orphan*/  uwb_rsv_set_state (struct uwb_rsv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_conflict_expanding(struct uwb_ie_drp *drp_ie, int ext_beacon_slot,
				      struct uwb_rsv *rsv, bool companion_only,
				      struct uwb_mas_bm *conflicting_mas)
{
	struct uwb_rc *rc = rsv->rc;
	struct uwb_drp_backoff_win *bow = &rc->bow;
	struct uwb_rsv_move *mv = &rsv->mv;
	int action;

	if (companion_only) {
		/* status of companion is 0 at this point */
		action = evaluate_conflict_action(drp_ie, ext_beacon_slot, rsv, 0);
		if (uwb_rsv_is_owner(rsv)) {
			switch(action) {
			case UWB_DRP_CONFLICT_ACT2:
			case UWB_DRP_CONFLICT_ACT3:
				uwb_rsv_set_state(rsv,
						UWB_RSV_STATE_O_ESTABLISHED);
				rsv->needs_release_companion_mas = false;
				if (bow->can_reserve_extra_mases == false)
					uwb_rsv_backoff_win_increment(rc);
				uwb_drp_avail_release(rsv->rc,
						&rsv->mv.companion_mas);
			}
		} else { /* rsv is target */
			switch(action) {
			case UWB_DRP_CONFLICT_ACT2:
			case UWB_DRP_CONFLICT_ACT3:
				uwb_rsv_set_state(rsv,
					UWB_RSV_STATE_T_EXPANDING_CONFLICT);
                                /* send_drp_avail_ie = true; */
			}
		}
	} else { /* also base part of the reservation is conflicting */
		if (uwb_rsv_is_owner(rsv)) {
			uwb_rsv_backoff_win_increment(rc);
			/* remove companion part */
			uwb_drp_avail_release(rsv->rc, &rsv->mv.companion_mas);

			/* drop some mases with reason modified */

			/* put in the companion the mases to be dropped */
			bitmap_andnot(mv->companion_mas.bm, rsv->mas.bm,
					conflicting_mas->bm, UWB_NUM_MAS);
			uwb_rsv_set_state(rsv, UWB_RSV_STATE_O_MODIFIED);
		} else { /* it is a target rsv */
			uwb_rsv_set_state(rsv, UWB_RSV_STATE_T_CONFLICT);
                        /* send_drp_avail_ie = true; */
		}
	}
}