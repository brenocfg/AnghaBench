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
struct uwb_rsv {scalar_t__ state; TYPE_1__ mas; struct uwb_rsv_move mv; } ;
struct uwb_rc_evt_drp {int dummy; } ;
struct uwb_rc {int dummy; } ;
struct uwb_mas_bm {int /*<<< orphan*/  bm; } ;
struct uwb_ie_drp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  UWB_NUM_MAS ; 
 scalar_t__ UWB_RSV_STATE_T_ACCEPTED ; 
 scalar_t__ UWB_RSV_STATE_T_CONFLICT ; 
 scalar_t__ UWB_RSV_STATE_T_EXPANDING_ACCEPTED ; 
 int /*<<< orphan*/  bitmap_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_drp_avail_reserve_pending (struct uwb_rc*,struct uwb_mas_bm*) ; 
 int /*<<< orphan*/  uwb_drp_handle_all_conflict_rsv (struct uwb_rc*,struct uwb_rc_evt_drp*,struct uwb_ie_drp*,struct uwb_mas_bm*) ; 
 int uwb_ie_drp_status (struct uwb_ie_drp*) ; 
 int /*<<< orphan*/  uwb_rsv_set_state (struct uwb_rsv*,scalar_t__) ; 

__attribute__((used)) static void uwb_drp_process_target_accepted(struct uwb_rc *rc,
	struct uwb_rsv *rsv, struct uwb_rc_evt_drp *drp_evt,
	struct uwb_ie_drp *drp_ie, struct uwb_mas_bm *mas)
{
	struct uwb_rsv_move *mv = &rsv->mv;
	int status;

	status = uwb_ie_drp_status(drp_ie);

	if (rsv->state == UWB_RSV_STATE_T_CONFLICT) {
		uwb_rsv_set_state(rsv, UWB_RSV_STATE_T_CONFLICT);
		return;
	}

	if (rsv->state == UWB_RSV_STATE_T_EXPANDING_ACCEPTED) {
		/* drp_ie is companion */
		if (!bitmap_equal(rsv->mas.bm, mas->bm, UWB_NUM_MAS)) {
			/* stroke companion */
			uwb_rsv_set_state(rsv,
				UWB_RSV_STATE_T_EXPANDING_ACCEPTED);
		}
	} else {
		if (!bitmap_equal(rsv->mas.bm, mas->bm, UWB_NUM_MAS)) {
			if (uwb_drp_avail_reserve_pending(rc, mas) == -EBUSY) {
				/* FIXME: there is a conflict, find
				 * the conflicting reservations and
				 * take a sensible action. Consider
				 * that in drp_ie there is the
				 * "neighbour" */
				uwb_drp_handle_all_conflict_rsv(rc, drp_evt,
						drp_ie, mas);
			} else {
				/* accept the extra reservation */
				bitmap_copy(mv->companion_mas.bm, mas->bm,
								UWB_NUM_MAS);
				uwb_rsv_set_state(rsv,
					UWB_RSV_STATE_T_EXPANDING_ACCEPTED);
			}
		} else {
			if (status) {
				uwb_rsv_set_state(rsv,
						UWB_RSV_STATE_T_ACCEPTED);
			}
		}

	}
}