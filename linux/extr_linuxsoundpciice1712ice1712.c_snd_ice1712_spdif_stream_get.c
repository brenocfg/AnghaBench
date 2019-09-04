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
struct TYPE_3__ {int /*<<< orphan*/  (* stream_get ) (struct snd_ice1712*,struct snd_ctl_elem_value*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct snd_ice1712 {TYPE_2__ spdif; } ;
struct snd_ctl_elem_value {int dummy; } ;

/* Variables and functions */
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  stub1 (struct snd_ice1712*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int snd_ice1712_spdif_stream_get(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	if (ice->spdif.ops.stream_get)
		ice->spdif.ops.stream_get(ice, ucontrol);
	return 0;
}