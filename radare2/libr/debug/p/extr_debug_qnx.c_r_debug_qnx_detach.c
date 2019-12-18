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
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qnxr_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_buf ; 

__attribute__((used)) static int r_debug_qnx_detach (RDebug *dbg, int pid) {
	qnxr_disconnect (desc);
	free (reg_buf);
	return true;
}