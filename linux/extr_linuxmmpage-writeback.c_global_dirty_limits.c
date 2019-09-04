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
struct dirty_throttle_control {unsigned long bg_thresh; unsigned long thresh; int /*<<< orphan*/  avail; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDTC_INIT_NO_WB ; 
 int /*<<< orphan*/  domain_dirty_limits (struct dirty_throttle_control*) ; 
 int /*<<< orphan*/  global_dirtyable_memory () ; 

void global_dirty_limits(unsigned long *pbackground, unsigned long *pdirty)
{
	struct dirty_throttle_control gdtc = { GDTC_INIT_NO_WB };

	gdtc.avail = global_dirtyable_memory();
	domain_dirty_limits(&gdtc);

	*pbackground = gdtc.bg_thresh;
	*pdirty = gdtc.thresh;
}