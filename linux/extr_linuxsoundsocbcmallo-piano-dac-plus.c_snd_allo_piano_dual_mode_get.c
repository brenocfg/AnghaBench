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
struct snd_soc_card {struct glb_pool* drvdata; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct glb_pool {int /*<<< orphan*/  dual_mode; } ;

/* Variables and functions */
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_allo_piano_dual_mode_get(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	struct glb_pool *glb_ptr = card->drvdata;

	ucontrol->value.integer.value[0] = glb_ptr->dual_mode;

	return 0;
}