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
typedef  scalar_t__ u8 ;
struct esas2r_target {scalar_t__ buffered_target_state; scalar_t__ target_state; } ;
struct esas2r_adapter {int /*<<< orphan*/  mem_lock; struct esas2r_target* targetdb_end; struct esas2r_target* targetdb; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_DISC_PENDING ; 
 scalar_t__ TS_INVALID ; 
 scalar_t__ esas2r_targ_get_id (struct esas2r_target*,struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_target_state_changed (struct esas2r_adapter*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  esas2r_trace (char*,scalar_t__) ; 
 int /*<<< orphan*/  esas2r_trace_enter () ; 
 int /*<<< orphan*/  esas2r_trace_exit () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void esas2r_targ_db_report_changes(struct esas2r_adapter *a)
{
	struct esas2r_target *t;
	unsigned long flags;

	esas2r_trace_enter();

	if (test_bit(AF_DISC_PENDING, &a->flags)) {
		esas2r_trace_exit();
		return;
	}

	for (t = a->targetdb; t < a->targetdb_end; t++) {
		u8 state = TS_INVALID;

		spin_lock_irqsave(&a->mem_lock, flags);
		if (t->buffered_target_state != t->target_state)
			state = t->buffered_target_state = t->target_state;

		spin_unlock_irqrestore(&a->mem_lock, flags);
		if (state != TS_INVALID) {
			esas2r_trace("targ_db_report_changes:%d",
				     esas2r_targ_get_id(
					     t,
					     a));
			esas2r_trace("state:%d", state);

			esas2r_target_state_changed(a,
						    esas2r_targ_get_id(t,
								       a),
						    state);
		}
	}

	esas2r_trace_exit();
}