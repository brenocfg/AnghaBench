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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct snd_ff {int /*<<< orphan*/  card; scalar_t__ registered; TYPE_1__ dwork; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct snd_ff* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_free (struct snd_ff*) ; 
 int /*<<< orphan*/  snd_card_free_when_closed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_ff_remove(struct fw_unit *unit)
{
	struct snd_ff *ff = dev_get_drvdata(&unit->device);

	/*
	 * Confirm to stop the work for registration before the sound card is
	 * going to be released. The work is not scheduled again because bus
	 * reset handler is not called anymore.
	 */
	cancel_work_sync(&ff->dwork.work);

	if (ff->registered) {
		/* No need to wait for releasing card object in this context. */
		snd_card_free_when_closed(ff->card);
	} else {
		/* Don't forget this case. */
		ff_free(ff);
	}
}