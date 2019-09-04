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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __kmemleak_do_cleanup () ; 
 int /*<<< orphan*/  kmemleak_found_leaks ; 
 scalar_t__ kmemleak_free_enabled ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  scan_mutex ; 
 int /*<<< orphan*/  stop_scan_thread () ; 

__attribute__((used)) static void kmemleak_do_cleanup(struct work_struct *work)
{
	stop_scan_thread();

	mutex_lock(&scan_mutex);
	/*
	 * Once it is made sure that kmemleak_scan has stopped, it is safe to no
	 * longer track object freeing. Ordering of the scan thread stopping and
	 * the memory accesses below is guaranteed by the kthread_stop()
	 * function.
	 */
	kmemleak_free_enabled = 0;
	mutex_unlock(&scan_mutex);

	if (!kmemleak_found_leaks)
		__kmemleak_do_cleanup();
	else
		pr_info("Kmemleak disabled without freeing internal data. Reclaim the memory with \"echo clear > /sys/kernel/debug/kmemleak\".\n");
}