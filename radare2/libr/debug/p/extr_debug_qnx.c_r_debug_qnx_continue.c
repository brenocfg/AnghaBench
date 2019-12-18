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
 int /*<<< orphan*/  desc ; 
 int /*<<< orphan*/  qnxr_continue (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int r_debug_qnx_continue (RDebug *dbg, int pid, int tid, int sig) {
	qnxr_continue (desc, -1);
	return true;
}