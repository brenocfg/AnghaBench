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
typedef  int /*<<< orphan*/  RDebug ;

/* Variables and functions */
 int R_DEBUG_REASON_UNKNOWN ; 
 int /*<<< orphan*/  check_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  desc ; 
 int /*<<< orphan*/  gdbr_step (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int r_debug_gdb_step(RDebug *dbg) {
	check_connection (dbg);
	if (!desc) {
		return R_DEBUG_REASON_UNKNOWN;
	}
	gdbr_step (desc, -1); // TODO handle thread specific step?
	return true;
}