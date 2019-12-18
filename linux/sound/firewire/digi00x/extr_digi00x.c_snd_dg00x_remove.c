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
struct snd_dg00x {int /*<<< orphan*/  unit; int /*<<< orphan*/  mutex; int /*<<< orphan*/  card; scalar_t__ registered; int /*<<< orphan*/  dwork; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct snd_dg00x* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_unit_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_dg00x_remove(struct fw_unit *unit)
{
	struct snd_dg00x *dg00x = dev_get_drvdata(&unit->device);

	/*
	 * Confirm to stop the work for registration before the sound card is
	 * going to be released. The work is not scheduled again because bus
	 * reset handler is not called anymore.
	 */
	cancel_delayed_work_sync(&dg00x->dwork);

	if (dg00x->registered) {
		// Block till all of ALSA character devices are released.
		snd_card_free(dg00x->card);
	}

	mutex_destroy(&dg00x->mutex);
	fw_unit_put(dg00x->unit);
}