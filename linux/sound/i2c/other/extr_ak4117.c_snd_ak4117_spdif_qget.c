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
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct ak4117 {int dummy; } ;

/* Variables and functions */
 scalar_t__ AK4117_REG_QSUB_ADDR ; 
 unsigned int AK4117_REG_QSUB_SIZE ; 
 int /*<<< orphan*/  reg_read (struct ak4117*,scalar_t__) ; 
 struct ak4117* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ak4117_spdif_qget(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct ak4117 *chip = snd_kcontrol_chip(kcontrol);
	unsigned i;

	for (i = 0; i < AK4117_REG_QSUB_SIZE; i++)
		ucontrol->value.bytes.data[i] = reg_read(chip, AK4117_REG_QSUB_ADDR + i);
	return 0;
}