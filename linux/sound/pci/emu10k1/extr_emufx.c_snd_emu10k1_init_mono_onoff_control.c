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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  iface; } ;
struct snd_emu10k1_fx8010_control_gpr {int vcount; int count; int* value; int max; int /*<<< orphan*/  translation; scalar_t__ min; scalar_t__* gpr; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU10K1_GPR_TRANSLATION_ONOFF ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
snd_emu10k1_init_mono_onoff_control(struct snd_emu10k1_fx8010_control_gpr *ctl,
				    const char *name, int gpr, int defval)
{
	ctl->id.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	strcpy(ctl->id.name, name);
	ctl->vcount = ctl->count = 1;
	ctl->gpr[0] = gpr + 0; ctl->value[0] = defval;
	ctl->min = 0;
	ctl->max = 1;
	ctl->translation = EMU10K1_GPR_TRANSLATION_ONOFF;
}