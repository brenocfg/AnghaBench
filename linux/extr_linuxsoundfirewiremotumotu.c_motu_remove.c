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
struct snd_motu {int /*<<< orphan*/  card; scalar_t__ registered; int /*<<< orphan*/  dwork; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct snd_motu* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  motu_free (struct snd_motu*) ; 
 int /*<<< orphan*/  snd_card_free_when_closed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void motu_remove(struct fw_unit *unit)
{
	struct snd_motu *motu = dev_get_drvdata(&unit->device);

	/*
	 * Confirm to stop the work for registration before the sound card is
	 * going to be released. The work is not scheduled again because bus
	 * reset handler is not called anymore.
	 */
	cancel_delayed_work_sync(&motu->dwork);

	if (motu->registered) {
		/* No need to wait for releasing card object in this context. */
		snd_card_free_when_closed(motu->card);
	} else {
		/* Don't forget this case. */
		motu_free(motu);
	}
}