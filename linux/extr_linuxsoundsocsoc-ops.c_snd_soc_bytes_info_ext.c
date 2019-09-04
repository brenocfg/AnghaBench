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
struct soc_bytes_ext {int /*<<< orphan*/  max; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct snd_ctl_elem_info {int /*<<< orphan*/  count; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_BYTES ; 

int snd_soc_bytes_info_ext(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_info *ucontrol)
{
	struct soc_bytes_ext *params = (void *)kcontrol->private_value;

	ucontrol->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	ucontrol->count = params->max;

	return 0;
}