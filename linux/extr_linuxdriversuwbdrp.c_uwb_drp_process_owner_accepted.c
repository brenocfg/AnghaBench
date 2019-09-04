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
struct TYPE_3__ {int /*<<< orphan*/  bm; } ;
struct uwb_rsv_move {TYPE_1__ companion_mas; } ;
struct TYPE_4__ {int /*<<< orphan*/  bm; } ;
struct uwb_rsv {int state; TYPE_2__ mas; struct uwb_rsv_move mv; } ;
struct uwb_mas_bm {int /*<<< orphan*/  bm; } ;

/* Variables and functions */
 int /*<<< orphan*/  UWB_NUM_MAS ; 
#define  UWB_RSV_STATE_O_ESTABLISHED 134 
#define  UWB_RSV_STATE_O_INITIATED 133 
#define  UWB_RSV_STATE_O_MODIFIED 132 
#define  UWB_RSV_STATE_O_MOVE_COMBINING 131 
#define  UWB_RSV_STATE_O_MOVE_EXPANDING 130 
#define  UWB_RSV_STATE_O_MOVE_REDUCING 129 
#define  UWB_RSV_STATE_O_PENDING 128 
 int /*<<< orphan*/  bitmap_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_rsv_set_state (struct uwb_rsv*,int const) ; 

__attribute__((used)) static void uwb_drp_process_owner_accepted(struct uwb_rsv *rsv,
						struct uwb_mas_bm *mas)
{
	struct uwb_rsv_move *mv = &rsv->mv;

	switch (rsv->state) {
	case UWB_RSV_STATE_O_PENDING:
	case UWB_RSV_STATE_O_INITIATED:
	case UWB_RSV_STATE_O_ESTABLISHED:
		uwb_rsv_set_state(rsv, UWB_RSV_STATE_O_ESTABLISHED);
		break;
	case UWB_RSV_STATE_O_MODIFIED:
		if (bitmap_equal(mas->bm, rsv->mas.bm, UWB_NUM_MAS))
			uwb_rsv_set_state(rsv, UWB_RSV_STATE_O_ESTABLISHED);
		else
			uwb_rsv_set_state(rsv, UWB_RSV_STATE_O_MODIFIED);
		break;

	case UWB_RSV_STATE_O_MOVE_REDUCING: /* shouldn' t be a problem */
		if (bitmap_equal(mas->bm, rsv->mas.bm, UWB_NUM_MAS))
			uwb_rsv_set_state(rsv, UWB_RSV_STATE_O_ESTABLISHED);
		else
			uwb_rsv_set_state(rsv, UWB_RSV_STATE_O_MOVE_REDUCING);
		break;
	case UWB_RSV_STATE_O_MOVE_EXPANDING:
		if (bitmap_equal(mas->bm, mv->companion_mas.bm, UWB_NUM_MAS)) {
			/* Companion reservation accepted */
			uwb_rsv_set_state(rsv, UWB_RSV_STATE_O_MOVE_COMBINING);
		} else {
			uwb_rsv_set_state(rsv, UWB_RSV_STATE_O_MOVE_EXPANDING);
		}
		break;
	case UWB_RSV_STATE_O_MOVE_COMBINING:
		if (bitmap_equal(mas->bm, rsv->mas.bm, UWB_NUM_MAS))
			uwb_rsv_set_state(rsv, UWB_RSV_STATE_O_MOVE_REDUCING);
		else
			uwb_rsv_set_state(rsv, UWB_RSV_STATE_O_MOVE_COMBINING);
		break;
	default:
		break;
	}
}