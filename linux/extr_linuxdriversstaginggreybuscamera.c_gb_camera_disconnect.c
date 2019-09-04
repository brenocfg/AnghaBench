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
struct gb_camera {int /*<<< orphan*/  module; } ;
struct gb_bundle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_camera_cleanup (struct gb_camera*) ; 
 int /*<<< orphan*/  gb_camera_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_pm_runtime_get_noresume (struct gb_bundle*) ; 
 int gb_pm_runtime_get_sync (struct gb_bundle*) ; 
 struct gb_camera* greybus_get_drvdata (struct gb_bundle*) ; 

__attribute__((used)) static void gb_camera_disconnect(struct gb_bundle *bundle)
{
	struct gb_camera *gcam = greybus_get_drvdata(bundle);
	int ret;

	ret = gb_pm_runtime_get_sync(bundle);
	if (ret)
		gb_pm_runtime_get_noresume(bundle);

	gb_camera_cleanup(gcam);
	gb_camera_unregister(&gcam->module);
}