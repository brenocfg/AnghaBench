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
 int /*<<< orphan*/ * kdb_current_regs ; 
 int /*<<< orphan*/ * kdb_current_task ; 
 int kdb_initial_cpu ; 

int kdb_common_deinit_state(void)
{
	kdb_initial_cpu = -1;
	kdb_current_task = NULL;
	kdb_current_regs = NULL;
	return 0;
}