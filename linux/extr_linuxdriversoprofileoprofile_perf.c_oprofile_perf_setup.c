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
 int /*<<< orphan*/  op_perf_setup () ; 
 int /*<<< orphan*/  oprofilefs_lock ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oprofile_perf_setup(void)
{
	raw_spin_lock(&oprofilefs_lock);
	op_perf_setup();
	raw_spin_unlock(&oprofilefs_lock);
	return 0;
}