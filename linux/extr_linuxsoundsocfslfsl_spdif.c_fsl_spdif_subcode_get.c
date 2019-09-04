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
struct spdif_mixer_control {int ready_buf; int /*<<< orphan*/  ctl_lock; int /*<<< orphan*/ * subcode; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * subcode; } ;
struct TYPE_4__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct fsl_spdif_priv {struct spdif_mixer_control fsl_spdif_control; } ;

/* Variables and functions */
 int EAGAIN ; 
 int SPDIF_UBITS_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct snd_soc_dai* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct fsl_spdif_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fsl_spdif_subcode_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	struct fsl_spdif_priv *spdif_priv = snd_soc_dai_get_drvdata(cpu_dai);
	struct spdif_mixer_control *ctrl = &spdif_priv->fsl_spdif_control;
	unsigned long flags;
	int ret = -EAGAIN;

	spin_lock_irqsave(&ctrl->ctl_lock, flags);
	if (ctrl->ready_buf) {
		int idx = (ctrl->ready_buf - 1) * SPDIF_UBITS_SIZE;
		memcpy(&ucontrol->value.iec958.subcode[0],
				&ctrl->subcode[idx], SPDIF_UBITS_SIZE);
		ret = 0;
	}
	spin_unlock_irqrestore(&ctrl->ctl_lock, flags);

	return ret;
}