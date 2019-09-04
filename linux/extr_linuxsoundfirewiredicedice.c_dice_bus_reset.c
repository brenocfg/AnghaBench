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
struct snd_dice {int /*<<< orphan*/  mutex; scalar_t__ registered; int /*<<< orphan*/  dwork; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct snd_dice* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_dice_stream_update_duplex (struct snd_dice*) ; 
 int /*<<< orphan*/  snd_dice_transaction_reinit (struct snd_dice*) ; 
 int /*<<< orphan*/  snd_fw_schedule_registration (struct fw_unit*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dice_bus_reset(struct fw_unit *unit)
{
	struct snd_dice *dice = dev_get_drvdata(&unit->device);

	/* Postpone a workqueue for deferred registration. */
	if (!dice->registered)
		snd_fw_schedule_registration(unit, &dice->dwork);

	/* The handler address register becomes initialized. */
	snd_dice_transaction_reinit(dice);

	/*
	 * After registration, userspace can start packet streaming, then this
	 * code block works fine.
	 */
	if (dice->registered) {
		mutex_lock(&dice->mutex);
		snd_dice_stream_update_duplex(dice);
		mutex_unlock(&dice->mutex);
	}
}