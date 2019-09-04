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
struct snd_efw {int /*<<< orphan*/  mutex; scalar_t__ registered; int /*<<< orphan*/  unit; int /*<<< orphan*/  dwork; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct snd_efw* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_efw_stream_update_duplex (struct snd_efw*) ; 
 int /*<<< orphan*/  snd_efw_transaction_bus_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_fw_schedule_registration (struct fw_unit*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void efw_update(struct fw_unit *unit)
{
	struct snd_efw *efw = dev_get_drvdata(&unit->device);

	/* Postpone a workqueue for deferred registration. */
	if (!efw->registered)
		snd_fw_schedule_registration(unit, &efw->dwork);

	snd_efw_transaction_bus_reset(efw->unit);

	/*
	 * After registration, userspace can start packet streaming, then this
	 * code block works fine.
	 */
	if (efw->registered) {
		mutex_lock(&efw->mutex);
		snd_efw_stream_update_duplex(efw);
		mutex_unlock(&efw->mutex);
	}
}