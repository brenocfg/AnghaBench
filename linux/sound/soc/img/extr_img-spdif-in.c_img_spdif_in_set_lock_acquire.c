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
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct img_spdif_in {int lock_acquire; int /*<<< orphan*/  lock; scalar_t__ active; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IMG_SPDIF_IN_CTL ; 
 int IMG_SPDIF_IN_CTL_LOCKHI_MASK ; 
 int IMG_SPDIF_IN_CTL_LOCKHI_SHIFT ; 
 int img_spdif_in_readl (struct img_spdif_in*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_spdif_in_writel (struct img_spdif_in*,int,int /*<<< orphan*/ ) ; 
 struct snd_soc_dai* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct img_spdif_in* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int img_spdif_in_set_lock_acquire(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	struct img_spdif_in *spdif = snd_soc_dai_get_drvdata(cpu_dai);
	unsigned long flags;
	u32 reg;

	spin_lock_irqsave(&spdif->lock, flags);

	if (spdif->active) {
		spin_unlock_irqrestore(&spdif->lock, flags);
		return -EBUSY;
	}

	spdif->lock_acquire = ucontrol->value.integer.value[0];

	reg = img_spdif_in_readl(spdif, IMG_SPDIF_IN_CTL);
	reg &= ~IMG_SPDIF_IN_CTL_LOCKHI_MASK;
	reg |= (spdif->lock_acquire << IMG_SPDIF_IN_CTL_LOCKHI_SHIFT) &
		IMG_SPDIF_IN_CTL_LOCKHI_MASK;
	img_spdif_in_writel(spdif, reg, IMG_SPDIF_IN_CTL);

	spin_unlock_irqrestore(&spdif->lock, flags);

	return 0;
}