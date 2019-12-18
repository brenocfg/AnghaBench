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
struct snd_soc_dai {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct img_spdif_in {int /*<<< orphan*/  lock; int /*<<< orphan*/  single_freq; int /*<<< orphan*/ * multi_freqs; scalar_t__ multi_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_SPDIF_IN_STATUS ; 
 int IMG_SPDIF_IN_STATUS_LOCK_MASK ; 
 int IMG_SPDIF_IN_STATUS_SAM_MASK ; 
 int IMG_SPDIF_IN_STATUS_SAM_SHIFT ; 
 int img_spdif_in_readl (struct img_spdif_in*,int /*<<< orphan*/ ) ; 
 struct snd_soc_dai* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct img_spdif_in* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int img_spdif_in_get_lock_freq(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *uc)
{
	struct snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	struct img_spdif_in *spdif = snd_soc_dai_get_drvdata(cpu_dai);
	u32 reg;
	int i;
	unsigned long flags;

	spin_lock_irqsave(&spdif->lock, flags);

	reg = img_spdif_in_readl(spdif, IMG_SPDIF_IN_STATUS);
	if (reg & IMG_SPDIF_IN_STATUS_LOCK_MASK) {
		if (spdif->multi_freq) {
			i = ((reg & IMG_SPDIF_IN_STATUS_SAM_MASK) >>
					IMG_SPDIF_IN_STATUS_SAM_SHIFT) - 1;
			uc->value.integer.value[0] = spdif->multi_freqs[i];
		} else {
			uc->value.integer.value[0] = spdif->single_freq;
		}
	} else {
		uc->value.integer.value[0] = 0;
	}

	spin_unlock_irqrestore(&spdif->lock, flags);

	return 0;
}