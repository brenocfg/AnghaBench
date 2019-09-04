#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * root_folder; int /*<<< orphan*/  monitor_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 TYPE_1__* state ; 

__attribute__((used)) static int rpi_axiperf_remove(struct platform_device *dev)
{
	int ret = 0;

	kthread_stop(state->monitor_thread);

	debugfs_remove_recursive(state->root_folder);
	state->root_folder = NULL;

	return ret;
}