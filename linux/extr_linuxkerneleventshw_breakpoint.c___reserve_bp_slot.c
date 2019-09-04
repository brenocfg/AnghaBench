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
typedef  scalar_t__ u64 ;
struct perf_event {int dummy; } ;
struct bp_busy_slots {scalar_t__ pinned; int /*<<< orphan*/  flexible; int /*<<< orphan*/  member_0; } ;
typedef  enum bp_type_idx { ____Placeholder_bp_type_idx } bp_type_idx ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 scalar_t__ HW_BREAKPOINT_EMPTY ; 
 scalar_t__ HW_BREAKPOINT_INVALID ; 
 int /*<<< orphan*/  constraints_initialized ; 
 int /*<<< orphan*/  fetch_bp_busy_slots (struct bp_busy_slots*,struct perf_event*,int) ; 
 int /*<<< orphan*/  fetch_this_slot (struct bp_busy_slots*,int) ; 
 int find_slot_idx (scalar_t__) ; 
 int hw_breakpoint_weight (struct perf_event*) ; 
 scalar_t__* nr_slots ; 
 int /*<<< orphan*/  toggle_bp_slot (struct perf_event*,int,int,int) ; 

__attribute__((used)) static int __reserve_bp_slot(struct perf_event *bp, u64 bp_type)
{
	struct bp_busy_slots slots = {0};
	enum bp_type_idx type;
	int weight;

	/* We couldn't initialize breakpoint constraints on boot */
	if (!constraints_initialized)
		return -ENOMEM;

	/* Basic checks */
	if (bp_type == HW_BREAKPOINT_EMPTY ||
	    bp_type == HW_BREAKPOINT_INVALID)
		return -EINVAL;

	type = find_slot_idx(bp_type);
	weight = hw_breakpoint_weight(bp);

	fetch_bp_busy_slots(&slots, bp, type);
	/*
	 * Simulate the addition of this breakpoint to the constraints
	 * and see the result.
	 */
	fetch_this_slot(&slots, weight);

	/* Flexible counters need to keep at least one slot */
	if (slots.pinned + (!!slots.flexible) > nr_slots[type])
		return -ENOSPC;

	toggle_bp_slot(bp, true, type, weight);

	return 0;
}