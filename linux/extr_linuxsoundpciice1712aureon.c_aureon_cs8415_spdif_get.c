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
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS8415_C_BUFFER ; 
 int /*<<< orphan*/  aureon_cs8415_read (struct snd_ice1712*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_ice1712_restore_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int aureon_cs8415_spdif_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	snd_ice1712_save_gpio_status(ice);
	aureon_cs8415_read(ice, CS8415_C_BUFFER, ucontrol->value.iec958.status, 24);
	snd_ice1712_restore_gpio_status(ice);
	return 0;
}