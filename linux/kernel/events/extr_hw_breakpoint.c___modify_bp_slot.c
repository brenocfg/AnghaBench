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

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __release_bp_slot (struct perf_event*,int /*<<< orphan*/ ) ; 
 int __reserve_bp_slot (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __modify_bp_slot(struct perf_event *bp, u64 old_type, u64 new_type)
{
	int err;

	__release_bp_slot(bp, old_type);

	err = __reserve_bp_slot(bp, new_type);
	if (err) {
		/*
		 * Reserve the old_type slot back in case
		 * there's no space for the new type.
		 *
		 * This must succeed, because we just released
		 * the old_type slot in the __release_bp_slot
		 * call above. If not, something is broken.
		 */
		WARN_ON(__reserve_bp_slot(bp, old_type));
	}

	return err;
}