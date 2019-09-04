#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_kcontrol {scalar_t__ private_value; } ;
struct snd_ctl_elem_info {int /*<<< orphan*/  count; int /*<<< orphan*/  type; } ;
struct sigmadsp_control {int /*<<< orphan*/  num_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_BYTES ; 

__attribute__((used)) static int sigmadsp_ctrl_info(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_info *info)
{
	struct sigmadsp_control *ctrl = (void *)kcontrol->private_value;

	info->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	info->count = ctrl->num_bytes;

	return 0;
}