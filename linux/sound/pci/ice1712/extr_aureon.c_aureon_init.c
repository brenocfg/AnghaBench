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
struct TYPE_2__ {scalar_t__ subvendor; } ;
struct snd_ice1712 {int num_total_dacs; int num_total_adcs; int akm_codecs; int pm_suspend_enabled; int /*<<< orphan*/  pm_resume; void* akm; TYPE_1__ eeprom; struct aureon_spec* spec; } ;
struct snd_akm4xxx {int dummy; } ;
struct aureon_spec {void** master; void** vol; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ VT1724_SUBDEVICE_AUREON51_SKY ; 
 void* WM_VOL_MUTE ; 
 int aureon_reset (struct snd_ice1712*) ; 
 int /*<<< orphan*/  aureon_resume ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm_set_vol (struct snd_ice1712*,int,void*,void*) ; 

__attribute__((used)) static int aureon_init(struct snd_ice1712 *ice)
{
	struct aureon_spec *spec;
	int i, err;

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	ice->spec = spec;

	if (ice->eeprom.subvendor == VT1724_SUBDEVICE_AUREON51_SKY) {
		ice->num_total_dacs = 6;
		ice->num_total_adcs = 2;
	} else {
		/* aureon 7.1 and prodigy 7.1 */
		ice->num_total_dacs = 8;
		ice->num_total_adcs = 2;
	}

	/* to remember the register values of CS8415 */
	ice->akm = kzalloc(sizeof(struct snd_akm4xxx), GFP_KERNEL);
	if (!ice->akm)
		return -ENOMEM;
	ice->akm_codecs = 1;

	err = aureon_reset(ice);
	if (err != 0)
		return err;

	spec->master[0] = WM_VOL_MUTE;
	spec->master[1] = WM_VOL_MUTE;
	for (i = 0; i < ice->num_total_dacs; i++) {
		spec->vol[i] = WM_VOL_MUTE;
		wm_set_vol(ice, i, spec->vol[i], spec->master[i % 2]);
	}

#ifdef CONFIG_PM_SLEEP
	ice->pm_resume = aureon_resume;
	ice->pm_suspend_enabled = 1;
#endif

	return 0;
}