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
struct TYPE_3__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HR222_MICRO_CAPTURE_LEVEL_MAX ; 
 int /*<<< orphan*/  HR222_MICRO_CAPTURE_LEVEL_MIN ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 

__attribute__((used)) static int hr222_mic_vol_info(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_info *uinfo)
{
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.integer.min = HR222_MICRO_CAPTURE_LEVEL_MIN; /* -98 dB */
	/* gains from 9 dB to 31.5 dB not recommended; use micboost instead */
	uinfo->value.integer.max = HR222_MICRO_CAPTURE_LEVEL_MAX; /*  +7 dB */
	return 0;
}