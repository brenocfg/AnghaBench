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
typedef  int u32 ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_RME_CLK_AES_LOCK ; 
 int SND_RME_CLK_AES_SYNC ; 
 int SND_RME_CLK_SPDIF_LOCK ; 
 int SND_RME_CLK_SPDIF_SYNC ; 
 int SND_RME_CLOCK_LOCK ; 
 int SND_RME_CLOCK_NOLOCK ; 
 int SND_RME_CLOCK_SYNC ; 
#define  SND_RME_DOMAIN_AES 129 
#define  SND_RME_DOMAIN_SPDIF 128 
 int snd_rme_get_status1 (struct snd_kcontrol*,int*) ; 

__attribute__((used)) static int snd_rme_sync_state_get(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	u32 status1;
	int idx = SND_RME_CLOCK_NOLOCK;
	int err;

	err = snd_rme_get_status1(kcontrol, &status1);
	if (err < 0)
		return err;
	switch (kcontrol->private_value) {
	case SND_RME_DOMAIN_AES:  /* AES */
		if (status1 & SND_RME_CLK_AES_SYNC)
			idx = SND_RME_CLOCK_SYNC;
		else if (status1 & SND_RME_CLK_AES_LOCK)
			idx = SND_RME_CLOCK_LOCK;
		break;
	case SND_RME_DOMAIN_SPDIF:  /* SPDIF */
		if (status1 & SND_RME_CLK_SPDIF_SYNC)
			idx = SND_RME_CLOCK_SYNC;
		else if (status1 & SND_RME_CLK_SPDIF_LOCK)
			idx = SND_RME_CLOCK_LOCK;
		break;
	default:
		return -EINVAL;
	}
	ucontrol->value.enumerated.item[0] = idx;
	return 0;
}