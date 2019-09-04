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
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_perf_stop () ; 
 scalar_t__ oprofile_perf_enabled ; 
 int /*<<< orphan*/  oprofile_perf_mutex ; 

__attribute__((used)) static void oprofile_perf_stop(void)
{
	mutex_lock(&oprofile_perf_mutex);
	if (oprofile_perf_enabled)
		op_perf_stop();
	oprofile_perf_enabled = 0;
	mutex_unlock(&oprofile_perf_mutex);
}