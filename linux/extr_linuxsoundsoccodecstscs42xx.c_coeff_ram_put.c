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
struct tscs42xx {int coeff_ram_synced; int /*<<< orphan*/  coeff_ram_lock; int /*<<< orphan*/  pll_lock; int /*<<< orphan*/ * coeff_ram; } ;
struct soc_bytes_ext {size_t max; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct coeff_ram_ctl {size_t addr; struct soc_bytes_ext bytes_ext; } ;

/* Variables and functions */
 size_t COEFF_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ plls_locked (struct snd_soc_component*) ; 
 struct tscs42xx* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int write_coeff_ram (struct snd_soc_component*,int /*<<< orphan*/ *,size_t,unsigned int) ; 

__attribute__((used)) static int coeff_ram_put(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	struct tscs42xx *tscs42xx = snd_soc_component_get_drvdata(component);
	struct coeff_ram_ctl *ctl =
		(struct coeff_ram_ctl *)kcontrol->private_value;
	struct soc_bytes_ext *params = &ctl->bytes_ext;
	unsigned int coeff_cnt = params->max / COEFF_SIZE;
	int ret;

	mutex_lock(&tscs42xx->coeff_ram_lock);

	tscs42xx->coeff_ram_synced = false;

	memcpy(&tscs42xx->coeff_ram[ctl->addr * COEFF_SIZE],
		ucontrol->value.bytes.data, params->max);

	mutex_lock(&tscs42xx->pll_lock);

	if (plls_locked(component)) {
		ret = write_coeff_ram(component, tscs42xx->coeff_ram,
			ctl->addr, coeff_cnt);
		if (ret < 0) {
			dev_err(component->dev,
				"Failed to flush coeff ram cache (%d)\n", ret);
			goto exit;
		}
		tscs42xx->coeff_ram_synced = true;
	}

	ret = 0;
exit:
	mutex_unlock(&tscs42xx->pll_lock);

	mutex_unlock(&tscs42xx->coeff_ram_lock);

	return ret;
}