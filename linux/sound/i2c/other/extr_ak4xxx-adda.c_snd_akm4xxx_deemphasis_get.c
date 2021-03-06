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
 int AK_GET_SHIFT (int /*<<< orphan*/ ) ; 
 int snd_akm4xxx_get (struct snd_akm4xxx*,int,int) ; 
 struct snd_akm4xxx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_akm4xxx_deemphasis_get(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_value *ucontrol)
{
	struct snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	int chip = AK_GET_CHIP(kcontrol->private_value);
	int addr = AK_GET_ADDR(kcontrol->private_value);
	int shift = AK_GET_SHIFT(kcontrol->private_value);
	ucontrol->value.enumerated.item[0] =
		(snd_akm4xxx_get(ak, chip, addr) >> shift) & 3;
	return 0;
}