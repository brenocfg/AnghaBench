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
typedef  int /*<<< orphan*/  u8 ;
struct xonar_pcm179x {unsigned int dacs; int /*<<< orphan*/ ** pcm1796_regs; } ;
struct snd_kcontrol {struct oxygen* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {int /*<<< orphan*/  mutex; struct xonar_pcm179x* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCM1796_DME ; 
 int PCM1796_REG_BASE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcm1796_write (struct oxygen*,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int deemph_put(struct snd_kcontrol *ctl,
		       struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	struct xonar_pcm179x *data = chip->model_data;
	unsigned int i;
	int changed;
	u8 reg;

	mutex_lock(&chip->mutex);
	reg = data->pcm1796_regs[0][18 - PCM1796_REG_BASE];
	if (!value->value.integer.value[0])
		reg &= ~PCM1796_DME;
	else
		reg |= PCM1796_DME;
	changed = reg != data->pcm1796_regs[0][18 - PCM1796_REG_BASE];
	if (changed) {
		for (i = 0; i < data->dacs; ++i)
			pcm1796_write(chip, i, 18, reg);
	}
	mutex_unlock(&chip->mutex);
	return changed;
}