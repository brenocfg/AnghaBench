#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tid; } ;
typedef  TYPE_1__ RDebug ;

/* Variables and functions */
 int R_DEBUG_REASON_UNKNOWN ; 
 int /*<<< orphan*/  check_connection (TYPE_1__*) ; 
 int /*<<< orphan*/  desc ; 
 int /*<<< orphan*/  gdbr_step (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_debug_gdb_step(RDebug *dbg) {
	check_connection (dbg);
	if (!desc) {
		return R_DEBUG_REASON_UNKNOWN;
	}
	gdbr_step (desc, dbg->tid);
	return true;
}