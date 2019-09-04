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
typedef  int /*<<< orphan*/  u64 ;
struct perf_event {int dummy; } ;
typedef  enum bp_type_idx { ____Placeholder_bp_type_idx } bp_type_idx ;

/* Variables and functions */
 int find_slot_idx (int /*<<< orphan*/ ) ; 
 int hw_breakpoint_weight (struct perf_event*) ; 
 int /*<<< orphan*/  toggle_bp_slot (struct perf_event*,int,int,int) ; 

__attribute__((used)) static void __release_bp_slot(struct perf_event *bp, u64 bp_type)
{
	enum bp_type_idx type;
	int weight;

	type = find_slot_idx(bp_type);
	weight = hw_breakpoint_weight(bp);
	toggle_bp_slot(bp, false, type, weight);
}