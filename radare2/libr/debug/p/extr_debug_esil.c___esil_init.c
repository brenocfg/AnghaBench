#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int tid; int pid; } ;
typedef  TYPE_1__ RDebug ;

/* Variables and functions */

__attribute__((used)) static int __esil_init(RDebug *dbg) {
	dbg->tid = dbg->pid = 1;
	// aeim
	// aei
	return true;
}