#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  multiprocess; } ;
struct TYPE_6__ {TYPE_1__ stub_features; } ;
typedef  int /*<<< orphan*/  RDebug ;

/* Variables and functions */
 TYPE_2__* desc ; 
 int gdbr_detach (TYPE_2__*) ; 
 int gdbr_detach_pid (TYPE_2__*,int) ; 

__attribute__((used)) static int r_debug_gdb_detach(RDebug *dbg, int pid) {
	if (pid <= 0 || !desc->stub_features.multiprocess) {
		return gdbr_detach (desc);
	}
	return gdbr_detach_pid (desc, pid);
}