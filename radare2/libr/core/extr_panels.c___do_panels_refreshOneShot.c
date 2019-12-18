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
typedef  int /*<<< orphan*/  RCoreTaskOneShot ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 scalar_t__ __do_panels_refresh ; 
 int /*<<< orphan*/  r_core_task_enqueue_oneshot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __do_panels_refreshOneShot(RCore *core) {
	r_core_task_enqueue_oneshot (core, (RCoreTaskOneShot) __do_panels_refresh, core);
}