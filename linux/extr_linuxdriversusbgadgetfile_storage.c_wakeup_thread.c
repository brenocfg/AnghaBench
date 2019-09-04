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
struct fsg_dev {int thread_wakeup_needed; scalar_t__ thread_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 

__attribute__((used)) static void wakeup_thread(struct fsg_dev *fsg)
{
	/* Tell the main thread that something has happened */
	fsg->thread_wakeup_needed = 1;
	if (fsg->thread_task)
		wake_up_process(fsg->thread_task);
}