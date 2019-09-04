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
struct gb_hid {int /*<<< orphan*/  bundle; int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int gb_operation_sync (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gb_pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_hid_set_power(struct gb_hid *ghid, int type)
{
	int ret;

	ret = gb_pm_runtime_get_sync(ghid->bundle);
	if (ret)
		return ret;

	ret = gb_operation_sync(ghid->connection, type, NULL, 0, NULL, 0);

	gb_pm_runtime_put_autosuspend(ghid->bundle);

	return ret;
}