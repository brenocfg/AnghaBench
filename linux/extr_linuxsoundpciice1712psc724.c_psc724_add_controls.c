#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol_new {int private_value; int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  info; int /*<<< orphan*/  access; int /*<<< orphan*/  name; int /*<<< orphan*/  iface; } ;
struct snd_kcontrol {int dummy; } ;
struct snd_ice1712 {int /*<<< orphan*/  card; struct psc724_spec* spec; } ;
struct TYPE_10__ {TYPE_2__* ctl; } ;
struct TYPE_9__ {TYPE_1__* ctl; } ;
struct psc724_spec {TYPE_4__ wm8766; TYPE_3__ wm8776; } ;
typedef  int /*<<< orphan*/  cont ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/ * name; } ;
struct TYPE_7__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_5__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_READWRITE ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 size_t WM8766_CTL_CH1_SW ; 
 size_t WM8766_CTL_CH1_VOL ; 
 size_t WM8766_CTL_CH2_SW ; 
 size_t WM8766_CTL_CH2_VOL ; 
 size_t WM8766_CTL_CH3_SW ; 
 size_t WM8766_CTL_CH3_VOL ; 
 size_t WM8766_CTL_DEEMPH1_SW ; 
 size_t WM8766_CTL_DEEMPH2_SW ; 
 size_t WM8766_CTL_DEEMPH3_SW ; 
 size_t WM8766_CTL_IZD_SW ; 
 size_t WM8766_CTL_PHASE1_SW ; 
 size_t WM8766_CTL_PHASE2_SW ; 
 size_t WM8766_CTL_PHASE3_SW ; 
 size_t WM8766_CTL_ZC_SW ; 
 size_t WM8776_CTL_AUX_SW ; 
 size_t WM8776_CTL_DAC_IZD_SW ; 
 size_t WM8776_CTL_DAC_SW ; 
 size_t WM8776_CTL_DAC_VOL ; 
 size_t WM8776_CTL_DAC_ZC_SW ; 
 size_t WM8776_CTL_DEEMPH_SW ; 
 size_t WM8776_CTL_INPUT1_SW ; 
 size_t WM8776_CTL_INPUT2_SW ; 
 size_t WM8776_CTL_INPUT3_SW ; 
 size_t WM8776_CTL_INPUT4_SW ; 
 size_t WM8776_CTL_INPUT5_SW ; 
 size_t WM8776_CTL_PHASE_SW ; 
 int /*<<< orphan*/ * ain1_switch ; 
 int /*<<< orphan*/ * ain2_switch ; 
 int /*<<< orphan*/ * ain3_switch ; 
 int /*<<< orphan*/ * ain4_switch ; 
 int /*<<< orphan*/ * ain5_switch ; 
 int /*<<< orphan*/ * clfe_deemph ; 
 int /*<<< orphan*/ * clfe_phase ; 
 int /*<<< orphan*/ * clfe_switch ; 
 int /*<<< orphan*/ * clfe_volume ; 
 int /*<<< orphan*/ * front_deemph ; 
 int /*<<< orphan*/ * front_izd ; 
 int /*<<< orphan*/ * front_phase ; 
 int /*<<< orphan*/ * front_switch ; 
 int /*<<< orphan*/ * front_volume ; 
 int /*<<< orphan*/ * front_zc ; 
 int /*<<< orphan*/  memset (struct snd_kcontrol_new*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* psc724_cont ; 
 int /*<<< orphan*/  psc724_ctl_get ; 
 int /*<<< orphan*/  psc724_ctl_put ; 
 int /*<<< orphan*/ * rear_clfe_izd ; 
 int /*<<< orphan*/ * rear_clfe_zc ; 
 int /*<<< orphan*/ * rear_deemph ; 
 int /*<<< orphan*/ * rear_phase ; 
 int /*<<< orphan*/ * rear_switch ; 
 int /*<<< orphan*/ * rear_volume ; 
 int snd_ctl_add (int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_ctl_boolean_mono_info ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_wm8766_build_controls (TYPE_4__*) ; 
 int /*<<< orphan*/  snd_wm8776_build_controls (TYPE_3__*) ; 

__attribute__((used)) static int psc724_add_controls(struct snd_ice1712 *ice)
{
	struct snd_kcontrol_new cont;
	struct snd_kcontrol *ctl;
	int err, i;
	struct psc724_spec *spec = ice->spec;

	spec->wm8776.ctl[WM8776_CTL_DAC_VOL].name = front_volume;
	spec->wm8776.ctl[WM8776_CTL_DAC_SW].name = front_switch;
	spec->wm8776.ctl[WM8776_CTL_DAC_ZC_SW].name = front_zc;
	spec->wm8776.ctl[WM8776_CTL_AUX_SW].name = NULL;
	spec->wm8776.ctl[WM8776_CTL_DAC_IZD_SW].name = front_izd;
	spec->wm8776.ctl[WM8776_CTL_PHASE_SW].name = front_phase;
	spec->wm8776.ctl[WM8776_CTL_DEEMPH_SW].name = front_deemph;
	spec->wm8776.ctl[WM8776_CTL_INPUT1_SW].name = ain1_switch;
	spec->wm8776.ctl[WM8776_CTL_INPUT2_SW].name = ain2_switch;
	spec->wm8776.ctl[WM8776_CTL_INPUT3_SW].name = ain3_switch;
	spec->wm8776.ctl[WM8776_CTL_INPUT4_SW].name = ain4_switch;
	spec->wm8776.ctl[WM8776_CTL_INPUT5_SW].name = ain5_switch;
	snd_wm8776_build_controls(&spec->wm8776);
	spec->wm8766.ctl[WM8766_CTL_CH1_VOL].name = rear_volume;
	spec->wm8766.ctl[WM8766_CTL_CH2_VOL].name = clfe_volume;
	spec->wm8766.ctl[WM8766_CTL_CH3_VOL].name = NULL;
	spec->wm8766.ctl[WM8766_CTL_CH1_SW].name = rear_switch;
	spec->wm8766.ctl[WM8766_CTL_CH2_SW].name = clfe_switch;
	spec->wm8766.ctl[WM8766_CTL_CH3_SW].name = NULL;
	spec->wm8766.ctl[WM8766_CTL_PHASE1_SW].name = rear_phase;
	spec->wm8766.ctl[WM8766_CTL_PHASE2_SW].name = clfe_phase;
	spec->wm8766.ctl[WM8766_CTL_PHASE3_SW].name = NULL;
	spec->wm8766.ctl[WM8766_CTL_DEEMPH1_SW].name = rear_deemph;
	spec->wm8766.ctl[WM8766_CTL_DEEMPH2_SW].name = clfe_deemph;
	spec->wm8766.ctl[WM8766_CTL_DEEMPH3_SW].name = NULL;
	spec->wm8766.ctl[WM8766_CTL_IZD_SW].name = rear_clfe_izd;
	spec->wm8766.ctl[WM8766_CTL_ZC_SW].name = rear_clfe_zc;
	snd_wm8766_build_controls(&spec->wm8766);

	memset(&cont, 0, sizeof(cont));
	cont.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	for (i = 0; i < ARRAY_SIZE(psc724_cont); i++) {
		cont.private_value = i;
		cont.name = psc724_cont[i].name;
		cont.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
		cont.info = snd_ctl_boolean_mono_info;
		cont.get = psc724_ctl_get;
		cont.put = psc724_ctl_put;
		ctl = snd_ctl_new1(&cont, ice);
		if (!ctl)
			return -ENOMEM;
		err = snd_ctl_add(ice->card, ctl);
		if (err < 0)
			return err;
	}

	return 0;
}