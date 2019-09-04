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
struct snd_ff {scalar_t__ registered; int /*<<< orphan*/  dwork; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct snd_ff* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ff_stream_update_duplex (struct snd_ff*) ; 
 int /*<<< orphan*/  snd_ff_transaction_reregister (struct snd_ff*) ; 
 int /*<<< orphan*/  snd_fw_schedule_registration (struct fw_unit*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_ff_update(struct fw_unit *unit)
{
	struct snd_ff *ff = dev_get_drvdata(&unit->device);

	/* Postpone a workqueue for deferred registration. */
	if (!ff->registered)
		snd_fw_schedule_registration(unit, &ff->dwork);

	snd_ff_transaction_reregister(ff);

	if (ff->registered)
		snd_ff_stream_update_duplex(ff);
}