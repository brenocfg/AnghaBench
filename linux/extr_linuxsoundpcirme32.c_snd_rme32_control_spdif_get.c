#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  iec958; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct rme32 {int /*<<< orphan*/  wcreg_spdif; } ;

/* Variables and functions */
 struct rme32* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_rme32_convert_to_aes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_rme32_control_spdif_get(struct snd_kcontrol *kcontrol,
				       struct snd_ctl_elem_value *ucontrol)
{
	struct rme32 *rme32 = snd_kcontrol_chip(kcontrol);

	snd_rme32_convert_to_aes(&ucontrol->value.iec958,
				 rme32->wcreg_spdif);
	return 0;
}