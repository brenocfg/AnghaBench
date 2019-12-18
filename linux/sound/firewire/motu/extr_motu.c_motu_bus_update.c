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
struct snd_motu {int /*<<< orphan*/  dwork; int /*<<< orphan*/  registered; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct snd_motu* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_fw_schedule_registration (struct fw_unit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_motu_transaction_reregister (struct snd_motu*) ; 

__attribute__((used)) static void motu_bus_update(struct fw_unit *unit)
{
	struct snd_motu *motu = dev_get_drvdata(&unit->device);

	/* Postpone a workqueue for deferred registration. */
	if (!motu->registered)
		snd_fw_schedule_registration(unit, &motu->dwork);

	/* The handler address register becomes initialized. */
	snd_motu_transaction_reregister(motu);
}