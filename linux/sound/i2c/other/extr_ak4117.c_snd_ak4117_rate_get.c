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
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct ak4117 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4117_REG_RCS1 ; 
 int /*<<< orphan*/  external_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_read (struct ak4117*,int /*<<< orphan*/ ) ; 
 struct ak4117* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ak4117_rate_get(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct ak4117 *chip = snd_kcontrol_chip(kcontrol);

	ucontrol->value.integer.value[0] = external_rate(reg_read(chip, AK4117_REG_RCS1));
	return 0;
}