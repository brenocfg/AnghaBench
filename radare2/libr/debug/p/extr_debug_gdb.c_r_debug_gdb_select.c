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
 int /*<<< orphan*/ * desc ; 
 scalar_t__ gdbr_select (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * origriogdb ; 

__attribute__((used)) static bool r_debug_gdb_select(RDebug *dbg, int pid, int tid) {
	if (!desc || !*origriogdb) {
		desc = NULL;	//TODO hacky fix, please improve. I would suggest using a **desc instead of a *desc, so it is automatically updated
		return false;
	}

	return gdbr_select (desc, pid, tid) >= 0;
}