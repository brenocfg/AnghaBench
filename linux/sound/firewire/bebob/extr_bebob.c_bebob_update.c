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
struct snd_bebob {int /*<<< orphan*/  unit; int /*<<< orphan*/  dwork; int /*<<< orphan*/  registered; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct snd_bebob* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fcp_bus_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_fw_schedule_registration (struct fw_unit*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bebob_update(struct fw_unit *unit)
{
	struct snd_bebob *bebob = dev_get_drvdata(&unit->device);

	if (bebob == NULL)
		return;

	/* Postpone a workqueue for deferred registration. */
	if (!bebob->registered)
		snd_fw_schedule_registration(unit, &bebob->dwork);
	else
		fcp_bus_reset(bebob->unit);
}