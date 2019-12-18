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
struct snd_kcontrol {int dummy; } ;
struct snd_ice1712 {int dummy; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 unsigned char AK4114_IPS0 ; 
 int /*<<< orphan*/  AK4114_REG_IO1 ; 
 unsigned char prodigy192_ak4114_read (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int ak4114_input_sw_get(struct snd_kcontrol *kcontrol,
	       		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	unsigned char val;
		
	val = prodigy192_ak4114_read(ice, AK4114_REG_IO1);
	/* AK4114_IPS0 bit = 0 -> RX0 = Toslink
	 * AK4114_IPS0 bit = 1 -> RX1 = Coax
	 */
	ucontrol->value.enumerated.item[0] = (val & AK4114_IPS0) ? 1 : 0;
	return 0;
}