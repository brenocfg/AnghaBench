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
typedef  int /*<<< orphan*/  vortex_t ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int min; int max; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
 scalar_t__ VORTEX_IS_QUAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_vortex_pcm_vol_info(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_info *uinfo)
{
	vortex_t *vortex = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = (VORTEX_IS_QUAD(vortex) ? 4 : 2);
	uinfo->value.integer.min = -128;
	uinfo->value.integer.max = 32;
	return 0;
}