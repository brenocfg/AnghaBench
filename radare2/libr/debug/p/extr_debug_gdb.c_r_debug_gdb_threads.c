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
struct TYPE_4__ {scalar_t__ free; } ;
typedef  scalar_t__ RListFree ;
typedef  TYPE_1__ RList ;
typedef  int /*<<< orphan*/  RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  desc ; 
 TYPE_1__* gdbr_threads_list (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_debug_pid_free ; 

__attribute__((used)) static RList* r_debug_gdb_threads(RDebug *dbg, int pid) {
	RList *list;
	if ((list = gdbr_threads_list (desc, pid))) {
		list->free = (RListFree) &r_debug_pid_free;
	}
	return list;
}