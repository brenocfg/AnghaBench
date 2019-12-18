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
struct snd_emu10k1_fx8010_control_gpr {int vcount; int count; int* value; int max; int /*<<< orphan*/  translation; int /*<<< orphan*/  tlv; scalar_t__ min; scalar_t__* gpr; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU10K1_GPR_TRANSLATION_NONE ; 
 int /*<<< orphan*/  EMU10K1_GPR_TRANSLATION_TABLE100 ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 scalar_t__ high_res_gpr_volume ; 
 int /*<<< orphan*/  snd_emu10k1_db_linear ; 
 int /*<<< orphan*/  snd_emu10k1_db_scale1 ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
snd_emu10k1_init_mono_control(struct snd_emu10k1_fx8010_control_gpr *ctl,
			      const char *name, int gpr, int defval)
{
	ctl->id.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	strcpy(ctl->id.name, name);
	ctl->vcount = ctl->count = 1;
	ctl->gpr[0] = gpr + 0; ctl->value[0] = defval;
	if (high_res_gpr_volume) {
		ctl->min = 0;
		ctl->max = 0x7fffffff;
		ctl->tlv = snd_emu10k1_db_linear;
		ctl->translation = EMU10K1_GPR_TRANSLATION_NONE;
	} else {
		ctl->min = 0;
		ctl->max = 100;
		ctl->tlv = snd_emu10k1_db_scale1;
		ctl->translation = EMU10K1_GPR_TRANSLATION_TABLE100;
	}
}