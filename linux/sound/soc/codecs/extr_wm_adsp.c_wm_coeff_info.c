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
struct wm_coeff_ctl {int type; int len; } ;
struct soc_bytes_ext {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int step; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_info {int count; int /*<<< orphan*/  type; TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_BYTES ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
#define  WMFW_CTL_TYPE_ACKED 128 
 int /*<<< orphan*/  WM_ADSP_ACKED_CTL_MAX_VALUE ; 
 int /*<<< orphan*/  WM_ADSP_ACKED_CTL_MIN_VALUE ; 
 struct wm_coeff_ctl* bytes_ext_to_ctl (struct soc_bytes_ext*) ; 

__attribute__((used)) static int wm_coeff_info(struct snd_kcontrol *kctl,
			 struct snd_ctl_elem_info *uinfo)
{
	struct soc_bytes_ext *bytes_ext =
		(struct soc_bytes_ext *)kctl->private_value;
	struct wm_coeff_ctl *ctl = bytes_ext_to_ctl(bytes_ext);

	switch (ctl->type) {
	case WMFW_CTL_TYPE_ACKED:
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
		uinfo->value.integer.min = WM_ADSP_ACKED_CTL_MIN_VALUE;
		uinfo->value.integer.max = WM_ADSP_ACKED_CTL_MAX_VALUE;
		uinfo->value.integer.step = 1;
		uinfo->count = 1;
		break;
	default:
		uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
		uinfo->count = ctl->len;
		break;
	}

	return 0;
}