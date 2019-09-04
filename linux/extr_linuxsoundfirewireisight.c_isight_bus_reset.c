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
struct isight {int /*<<< orphan*/  mutex; int /*<<< orphan*/  resources; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct isight* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 scalar_t__ fw_iso_resources_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isight_pcm_abort (struct isight*) ; 
 int /*<<< orphan*/  isight_stop_streaming (struct isight*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isight_bus_reset(struct fw_unit *unit)
{
	struct isight *isight = dev_get_drvdata(&unit->device);

	if (fw_iso_resources_update(&isight->resources) < 0) {
		isight_pcm_abort(isight);

		mutex_lock(&isight->mutex);
		isight_stop_streaming(isight);
		mutex_unlock(&isight->mutex);
	}
}