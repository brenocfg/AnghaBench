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

/* Variables and functions */
 int /*<<< orphan*/  desc ; 
 scalar_t__ gdbr_select (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int r_debug_gdb_select(int pid, int tid) {
	if (!desc) {
		return false;
	}
	return gdbr_select (desc, pid, tid) >= 0;
}