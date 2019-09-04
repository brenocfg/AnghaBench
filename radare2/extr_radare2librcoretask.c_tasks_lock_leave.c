#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tasks_lock; } ;
typedef  int /*<<< orphan*/  TASK_SIGSET_T ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_th_lock_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasks_lock_block_signals_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tasks_lock_leave(RCore *core, TASK_SIGSET_T *old_sigset) {
	r_th_lock_leave (core->tasks_lock);
	tasks_lock_block_signals_reset (old_sigset);
}