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
struct snd_oxfw {struct fw_spkr* spec; } ;
struct snd_kcontrol {struct snd_oxfw* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_info {TYPE_1__ value; int /*<<< orphan*/  count; int /*<<< orphan*/  type; } ;
struct fw_spkr {int /*<<< orphan*/  volume_max; int /*<<< orphan*/  volume_min; int /*<<< orphan*/  mixer_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 

__attribute__((used)) static int spkr_volume_info(struct snd_kcontrol *control,
			    struct snd_ctl_elem_info *info)
{
	struct snd_oxfw *oxfw = control->private_data;
	struct fw_spkr *spkr = oxfw->spec;

	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = spkr->mixer_channels;
	info->value.integer.min = spkr->volume_min;
	info->value.integer.max = spkr->volume_max;

	return 0;
}