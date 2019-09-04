#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct soc_enum {unsigned int shift_l; int /*<<< orphan*/  reg; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {unsigned int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WM8804_PWRDN ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_soc_component_test_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,unsigned int) ; 
 struct snd_soc_component* snd_soc_dapm_kcontrol_component (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_lock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_unlock (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static int txsrc_put(struct snd_kcontrol *kcontrol,
		     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct soc_enum *e = (struct soc_enum *)kcontrol->private_value;
	unsigned int val = ucontrol->value.enumerated.item[0] << e->shift_l;
	unsigned int mask = 1 << e->shift_l;
	unsigned int txpwr;

	if (val != 0 && val != mask)
		return -EINVAL;

	snd_soc_dapm_mutex_lock(dapm);

	if (snd_soc_component_test_bits(component, e->reg, mask, val)) {
		/* save the current power state of the transmitter */
		txpwr = snd_soc_component_read32(component, WM8804_PWRDN) & 0x4;

		/* power down the transmitter */
		snd_soc_component_update_bits(component, WM8804_PWRDN, 0x4, 0x4);

		/* set the tx source */
		snd_soc_component_update_bits(component, e->reg, mask, val);

		/* restore the transmitter's configuration */
		snd_soc_component_update_bits(component, WM8804_PWRDN, 0x4, txpwr);
	}

	snd_soc_dapm_mutex_unlock(dapm);

	return 0;
}