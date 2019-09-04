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
struct wl1271 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 

__attribute__((used)) static void chip_op_handler(struct wl1271 *wl, unsigned long value,
			    void *arg)
{
	int ret;
	int (*chip_op) (struct wl1271 *wl);

	if (!arg) {
		wl1271_warning("debugfs chip_op_handler with no callback");
		return;
	}

	ret = pm_runtime_get_sync(wl->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(wl->dev);

		return;
	}

	chip_op = arg;
	chip_op(wl);

	pm_runtime_mark_last_busy(wl->dev);
	pm_runtime_put_autosuspend(wl->dev);
}