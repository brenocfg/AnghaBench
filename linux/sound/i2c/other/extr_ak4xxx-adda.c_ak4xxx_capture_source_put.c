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
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_akm4xxx {int dummy; } ;

/* Variables and functions */
 int AK_GET_ADDR (int /*<<< orphan*/ ) ; 
 int AK_GET_CHIP (int /*<<< orphan*/ ) ; 
 int AK_GET_MASK (int /*<<< orphan*/ ) ; 
 int AK_GET_SHIFT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ak4xxx_capture_num_inputs (struct snd_akm4xxx*,int) ; 
 unsigned char snd_akm4xxx_get (struct snd_akm4xxx*,int,int) ; 
 int /*<<< orphan*/  snd_akm4xxx_write (struct snd_akm4xxx*,int,int,unsigned char) ; 
 struct snd_akm4xxx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int ak4xxx_capture_source_put(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	int mixer_ch = AK_GET_SHIFT(kcontrol->private_value);
	int chip = AK_GET_CHIP(kcontrol->private_value);
	int addr = AK_GET_ADDR(kcontrol->private_value);
	int mask = AK_GET_MASK(kcontrol->private_value);
	unsigned char oval, val;
	int num_names = ak4xxx_capture_num_inputs(ak, mixer_ch);

	if (ucontrol->value.enumerated.item[0] >= num_names)
		return -EINVAL;

	oval = snd_akm4xxx_get(ak, chip, addr);
	val = oval & ~mask;
	val |= ucontrol->value.enumerated.item[0] & mask;
	if (val != oval) {
		snd_akm4xxx_write(ak, chip, addr, val);
		return 1;
	}
	return 0;
}