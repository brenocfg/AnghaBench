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
struct ct_mixer {int dummy; } ;
struct ct_atc {TYPE_1__* card; scalar_t__ mixer; } ;
typedef  enum CTALSADEVS { ____Placeholder_CTALSADEVS } CTALSADEVS ;
struct TYPE_2__ {int /*<<< orphan*/  mixername; } ;

/* Variables and functions */
 int ct_mixer_kcontrols_create (struct ct_mixer*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

int ct_alsa_mix_create(struct ct_atc *atc,
		       enum CTALSADEVS device,
		       const char *device_name)
{
	int err;

	/* Create snd kcontrol instances on demand */
	/* vol_ctl.device = swh_ctl.device = device; */ /* better w/ device 0 */
	err = ct_mixer_kcontrols_create((struct ct_mixer *)atc->mixer);
	if (err)
		return err;

	strcpy(atc->card->mixername, device_name);

	return 0;
}