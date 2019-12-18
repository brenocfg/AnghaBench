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
typedef  int u32 ;
struct snd_kcontrol {int dummy; } ;
struct snd_emu10k1 {unsigned int i2c_capture_source; unsigned int** i2c_capture_volume; int /*<<< orphan*/  emu_lock; scalar_t__ port; } ;
struct TYPE_3__ {unsigned int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
typedef  int ngain ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_ATTEN_ADCL ; 
 int /*<<< orphan*/  ADC_ATTEN_ADCR ; 
 int /*<<< orphan*/  ADC_MUX ; 
 scalar_t__ A_IOCFG ; 
 int EINVAL ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  snd_emu10k1_i2c_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int) ; 
 struct snd_emu10k1* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_audigy_i2c_capture_source_put(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	unsigned int source_id;
	unsigned int ngain, ogain;
	u32 gpio;
	int change = 0;
	unsigned long flags;
	u32 source;
	/* If the capture source has changed,
	 * update the capture volume from the cached value
	 * for the particular source.
	 */
	source_id = ucontrol->value.enumerated.item[0];
	/* Limit: uinfo->value.enumerated.items = 2; */
	/*        emu->i2c_capture_volume */
	if (source_id >= 2)
		return -EINVAL;
	change = (emu->i2c_capture_source != source_id);
	if (change) {
		snd_emu10k1_i2c_write(emu, ADC_MUX, 0); /* Mute input */
		spin_lock_irqsave(&emu->emu_lock, flags);
		gpio = inl(emu->port + A_IOCFG);
		if (source_id==0)
			outl(gpio | 0x4, emu->port + A_IOCFG);
		else
			outl(gpio & ~0x4, emu->port + A_IOCFG);
		spin_unlock_irqrestore(&emu->emu_lock, flags);

		ngain = emu->i2c_capture_volume[source_id][0]; /* Left */
		ogain = emu->i2c_capture_volume[emu->i2c_capture_source][0]; /* Left */
		if (ngain != ogain)
			snd_emu10k1_i2c_write(emu, ADC_ATTEN_ADCL, ((ngain) & 0xff));
		ngain = emu->i2c_capture_volume[source_id][1]; /* Right */
		ogain = emu->i2c_capture_volume[emu->i2c_capture_source][1]; /* Right */
		if (ngain != ogain)
			snd_emu10k1_i2c_write(emu, ADC_ATTEN_ADCR, ((ngain) & 0xff));

		source = 1 << (source_id + 2);
		snd_emu10k1_i2c_write(emu, ADC_MUX, source); /* Set source */
		emu->i2c_capture_source = source_id;
	}
        return change;
}