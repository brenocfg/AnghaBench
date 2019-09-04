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
 int /*<<< orphan*/  r_core_task_enqueue_oneshot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ r_core_visual_anal_refresh ; 

__attribute__((used)) static void r_core_visual_anal_refresh_oneshot (RCore *core) {
	r_core_task_enqueue_oneshot (core, (RCoreTaskOneShot) r_core_visual_anal_refresh, core);
}