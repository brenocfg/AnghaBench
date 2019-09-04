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
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS8415_RATIO ; 
 unsigned char aureon_cs8415_get (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int aureon_cs8415_rate_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	unsigned char ratio;
	ratio = aureon_cs8415_get(ice, CS8415_RATIO);
	ucontrol->value.integer.value[0] = (int)((unsigned int)ratio * 750);
	return 0;
}