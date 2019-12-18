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
 int /*<<< orphan*/  TIF_MEMDIE ; 
 int /*<<< orphan*/  atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oom_victims ; 
 int /*<<< orphan*/  oom_victims_wait ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void exit_oom_victim(void)
{
	clear_thread_flag(TIF_MEMDIE);

	if (!atomic_dec_return(&oom_victims))
		wake_up_all(&oom_victims_wait);
}