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
 int EBUSY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_perf_start () ; 
 int oprofile_perf_enabled ; 
 int /*<<< orphan*/  oprofile_perf_mutex ; 

__attribute__((used)) static int oprofile_perf_start(void)
{
	int ret = -EBUSY;

	mutex_lock(&oprofile_perf_mutex);
	if (!oprofile_perf_enabled) {
		ret = 0;
		op_perf_start();
		oprofile_perf_enabled = 1;
	}
	mutex_unlock(&oprofile_perf_mutex);
	return ret;
}