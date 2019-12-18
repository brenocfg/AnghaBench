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
typedef  int /*<<< orphan*/  u32 ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int SND_RME_CLK_AES (int /*<<< orphan*/ ) ; 
 int SND_RME_CLK_SPDIF (int /*<<< orphan*/ ) ; 
 int SND_RME_CLK_SYSTEM (int /*<<< orphan*/ ) ; 
#define  SND_RME_DOMAIN_AES 130 
#define  SND_RME_DOMAIN_SPDIF 129 
#define  SND_RME_DOMAIN_SYSTEM 128 
 int SND_RME_RATE_IDX_AES_SPDIF_NUM ; 
 int snd_rme_get_status1 (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * snd_rme_rate_table ; 

__attribute__((used)) static int snd_rme_rate_get(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_value *ucontrol)
{
	u32 status1;
	u32 rate = 0;
	int idx;
	int err;

	err = snd_rme_get_status1(kcontrol, &status1);
	if (err < 0)
		return err;
	switch (kcontrol->private_value) {
	case SND_RME_DOMAIN_SYSTEM:
		idx = SND_RME_CLK_SYSTEM(status1);
		if (idx < ARRAY_SIZE(snd_rme_rate_table))
			rate = snd_rme_rate_table[idx];
		break;
	case SND_RME_DOMAIN_AES:
		idx = SND_RME_CLK_AES(status1);
		if (idx < SND_RME_RATE_IDX_AES_SPDIF_NUM)
			rate = snd_rme_rate_table[idx];
		break;
	case SND_RME_DOMAIN_SPDIF:
		idx = SND_RME_CLK_SPDIF(status1);
		if (idx < SND_RME_RATE_IDX_AES_SPDIF_NUM)
			rate = snd_rme_rate_table[idx];
		break;
	default:
		return -EINVAL;
	}
	ucontrol->value.integer.value[0] = rate;
	return 0;
}