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
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kgdb_break_tasklet_var ; 
 int /*<<< orphan*/  kgdb_breakpoint () ; 

__attribute__((used)) static void kgdb_tasklet_bpt(unsigned long ing)
{
	kgdb_breakpoint();
	atomic_set(&kgdb_break_tasklet_var, 0);
}