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
struct snd_oxfw {TYPE_1__* entry; int /*<<< orphan*/  mutex; scalar_t__ registered; int /*<<< orphan*/  unit; int /*<<< orphan*/  dwork; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {scalar_t__ vendor_id; } ;

/* Variables and functions */
 scalar_t__ OUI_STANTON ; 
 struct snd_oxfw* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fcp_bus_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_fw_schedule_registration (struct fw_unit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_oxfw_scs1x_update (struct snd_oxfw*) ; 
 int /*<<< orphan*/  snd_oxfw_stream_update_duplex (struct snd_oxfw*) ; 

__attribute__((used)) static void oxfw_bus_reset(struct fw_unit *unit)
{
	struct snd_oxfw *oxfw = dev_get_drvdata(&unit->device);

	if (!oxfw->registered)
		snd_fw_schedule_registration(unit, &oxfw->dwork);

	fcp_bus_reset(oxfw->unit);

	if (oxfw->registered) {
		mutex_lock(&oxfw->mutex);
		snd_oxfw_stream_update_duplex(oxfw);
		mutex_unlock(&oxfw->mutex);

		if (oxfw->entry->vendor_id == OUI_STANTON)
			snd_oxfw_scs1x_update(oxfw);
	}
}