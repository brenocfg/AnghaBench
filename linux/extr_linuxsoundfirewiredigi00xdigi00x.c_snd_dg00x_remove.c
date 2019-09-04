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
struct snd_dg00x {int /*<<< orphan*/  card; scalar_t__ registered; int /*<<< orphan*/  dwork; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct snd_dg00x* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dg00x_free (struct snd_dg00x*) ; 
 int /*<<< orphan*/  snd_card_free_when_closed (int /*<<< orphan*/ ) ; 

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
		/* No need to wait for releasing card object in this context. */
		snd_card_free_when_closed(dg00x->card);
	} else {
		/* Don't forget this case. */
		dg00x_free(dg00x);
	}
}