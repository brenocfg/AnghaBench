#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {struct oxygen* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_info {TYPE_2__ value; int /*<<< orphan*/  count; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int /*<<< orphan*/  dac_volume_max; int /*<<< orphan*/  dac_volume_min; int /*<<< orphan*/  dac_channels_mixer; } ;
struct oxygen {TYPE_3__ model; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 

__attribute__((used)) static int dac_volume_info(struct snd_kcontrol *ctl,
			   struct snd_ctl_elem_info *info)
{
	struct oxygen *chip = ctl->private_data;

	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = chip->model.dac_channels_mixer;
	info->value.integer.min = chip->model.dac_volume_min;
	info->value.integer.max = chip->model.dac_volume_max;
	return 0;
}