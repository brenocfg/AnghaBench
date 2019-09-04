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
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_4__ {int /*<<< orphan*/  max; scalar_t__ min; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_info {int count; TYPE_1__ value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBRI_MAX_GAIN ; 
 int /*<<< orphan*/  DBRI_MAX_VOLUME ; 
 scalar_t__ DBRI_PLAY ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 

__attribute__((used)) static int snd_cs4215_info_volume(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_info *uinfo)
{
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.integer.min = 0;
	if (kcontrol->private_value == DBRI_PLAY)
		uinfo->value.integer.max = DBRI_MAX_VOLUME;
	else
		uinfo->value.integer.max = DBRI_MAX_GAIN;
	return 0;
}