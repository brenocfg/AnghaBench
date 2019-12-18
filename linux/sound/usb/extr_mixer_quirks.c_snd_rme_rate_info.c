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
struct snd_kcontrol {int private_value; } ;
struct TYPE_4__ {int min; int max; scalar_t__ step; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_info {int count; TYPE_1__ value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
#define  SND_RME_DOMAIN_AES 130 
#define  SND_RME_DOMAIN_SPDIF 129 
#define  SND_RME_DOMAIN_SYSTEM 128 

__attribute__((used)) static int snd_rme_rate_info(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_info *uinfo)
{
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	switch (kcontrol->private_value) {
	case SND_RME_DOMAIN_SYSTEM:
		uinfo->value.integer.min = 32000;
		uinfo->value.integer.max = 800000;
		break;
	case SND_RME_DOMAIN_AES:
	case SND_RME_DOMAIN_SPDIF:
	default:
		uinfo->value.integer.min = 0;
		uinfo->value.integer.max = 200000;
	}
	uinfo->value.integer.step = 0;
	return 0;
}