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
 int /*<<< orphan*/  ext4_lazyinit_task ; 
 int /*<<< orphan*/  ext4_li_info ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext4_destroy_lazyinit_thread(void)
{
	/*
	 * If thread exited earlier
	 * there's nothing to be done.
	 */
	if (!ext4_li_info || !ext4_lazyinit_task)
		return;

	kthread_stop(ext4_lazyinit_task);
}