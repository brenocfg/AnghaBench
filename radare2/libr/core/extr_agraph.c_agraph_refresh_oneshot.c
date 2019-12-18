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
struct agraph_refresh_data {int /*<<< orphan*/  core; } ;
typedef  int /*<<< orphan*/  RCoreTaskOneShot ;

/* Variables and functions */
 scalar_t__ agraph_refresh ; 
 int /*<<< orphan*/  r_core_task_enqueue_oneshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct agraph_refresh_data*) ; 

__attribute__((used)) static void agraph_refresh_oneshot(struct agraph_refresh_data *grd) {
	r_core_task_enqueue_oneshot (grd->core, (RCoreTaskOneShot) agraph_refresh, grd);
}