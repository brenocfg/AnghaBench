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
struct TYPE_3__ {scalar_t__* status; } ;
struct TYPE_4__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct img_spdif_out {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_SPDIF_OUT_CSH_UV ; 
 int IMG_SPDIF_OUT_CSH_UV_CSH_MASK ; 
 int IMG_SPDIF_OUT_CSH_UV_CSH_SHIFT ; 
 int /*<<< orphan*/  IMG_SPDIF_OUT_CSL ; 
 int img_spdif_out_readl (struct img_spdif_out*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_spdif_out_writel (struct img_spdif_out*,int,int /*<<< orphan*/ ) ; 
 struct snd_soc_dai* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct img_spdif_out* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int img_spdif_out_set_status(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	struct img_spdif_out *spdif = snd_soc_dai_get_drvdata(cpu_dai);
	u32 reg;
	unsigned long flags;

	reg = ((u32)ucontrol->value.iec958.status[3] << 24);
	reg |= ((u32)ucontrol->value.iec958.status[2] << 16);
	reg |= ((u32)ucontrol->value.iec958.status[1] << 8);
	reg |= (u32)ucontrol->value.iec958.status[0];

	spin_lock_irqsave(&spdif->lock, flags);

	img_spdif_out_writel(spdif, reg, IMG_SPDIF_OUT_CSL);

	reg = img_spdif_out_readl(spdif, IMG_SPDIF_OUT_CSH_UV);
	reg &= ~IMG_SPDIF_OUT_CSH_UV_CSH_MASK;
	reg |= (u32)ucontrol->value.iec958.status[4] <<
			IMG_SPDIF_OUT_CSH_UV_CSH_SHIFT;
	img_spdif_out_writel(spdif, reg, IMG_SPDIF_OUT_CSH_UV);

	spin_unlock_irqrestore(&spdif->lock, flags);

	return 0;
}