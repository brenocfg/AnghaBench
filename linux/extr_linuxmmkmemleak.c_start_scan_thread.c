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
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmemleak_scan_thread ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/ * scan_thread ; 

__attribute__((used)) static void start_scan_thread(void)
{
	if (scan_thread)
		return;
	scan_thread = kthread_run(kmemleak_scan_thread, NULL, "kmemleak");
	if (IS_ERR(scan_thread)) {
		pr_warn("Failed to create the scan thread\n");
		scan_thread = NULL;
	}
}