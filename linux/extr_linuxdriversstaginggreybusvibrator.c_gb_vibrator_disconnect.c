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
struct gb_vibrator_device {int /*<<< orphan*/  connection; int /*<<< orphan*/  minor; int /*<<< orphan*/  dev; int /*<<< orphan*/  delayed_work; } ;
struct gb_bundle {int dummy; } ;

/* Variables and functions */
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_pm_runtime_get_noresume (struct gb_bundle*) ; 
 int gb_pm_runtime_get_sync (struct gb_bundle*) ; 
 struct gb_vibrator_device* greybus_get_drvdata (struct gb_bundle*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gb_vibrator_device*) ; 
 int /*<<< orphan*/  minors ; 
 int /*<<< orphan*/  turn_off (struct gb_vibrator_device*) ; 

__attribute__((used)) static void gb_vibrator_disconnect(struct gb_bundle *bundle)
{
	struct gb_vibrator_device *vib = greybus_get_drvdata(bundle);
	int ret;

	ret = gb_pm_runtime_get_sync(bundle);
	if (ret)
		gb_pm_runtime_get_noresume(bundle);

	if (cancel_delayed_work_sync(&vib->delayed_work))
		turn_off(vib);

	device_unregister(vib->dev);
	ida_simple_remove(&minors, vib->minor);
	gb_connection_disable(vib->connection);
	gb_connection_destroy(vib->connection);
	kfree(vib);
}