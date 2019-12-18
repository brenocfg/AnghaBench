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
typedef  int u8 ;
struct xonar_cs43xx {int* cs4398_regs; int* cs4362a_regs; } ;
struct snd_kcontrol {struct oxygen* private_data; } ;
struct TYPE_3__ {scalar_t__* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {int /*<<< orphan*/  mutex; struct xonar_cs43xx* model_data; } ;

/* Variables and functions */
 int CS4362A_FILT_SEL ; 
 int CS4398_FILT_SEL ; 
 int /*<<< orphan*/  cs4362a_write (struct oxygen*,int,int) ; 
 int /*<<< orphan*/  cs4398_write (struct oxygen*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rolloff_put(struct snd_kcontrol *ctl,
		       struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	struct xonar_cs43xx *data = chip->model_data;
	int changed;
	u8 reg;

	mutex_lock(&chip->mutex);
	reg = data->cs4398_regs[7];
	if (value->value.enumerated.item[0])
		reg |= CS4398_FILT_SEL;
	else
		reg &= ~CS4398_FILT_SEL;
	changed = reg != data->cs4398_regs[7];
	if (changed) {
		cs4398_write(chip, 7, reg);
		if (reg & CS4398_FILT_SEL)
			reg = data->cs4362a_regs[0x04] | CS4362A_FILT_SEL;
		else
			reg = data->cs4362a_regs[0x04] & ~CS4362A_FILT_SEL;
		cs4362a_write(chip, 0x04, reg);
	}
	mutex_unlock(&chip->mutex);
	return changed;
}