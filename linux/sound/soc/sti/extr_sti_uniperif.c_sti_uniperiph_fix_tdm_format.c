#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int u64 ;
struct TYPE_2__ {int slot_width; } ;
struct uniperif {TYPE_1__ tdm_slot; int /*<<< orphan*/  dev; } ;
struct snd_pcm_hw_rule {int /*<<< orphan*/  var; struct uniperif* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_mask {int /*<<< orphan*/ * bits; } ;

/* Variables and functions */
 int EINVAL ; 
 int SNDRV_MASK_MAX ; 
 int SNDRV_PCM_FMTBIT_S16_LE ; 
 int SNDRV_PCM_FMTBIT_S32_LE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct snd_mask* hw_param_mask (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int sti_uniperiph_fix_tdm_format(struct snd_pcm_hw_params *params,
				 struct snd_pcm_hw_rule *rule)
{
	struct uniperif *uni = rule->private;
	struct snd_mask *maskp = hw_param_mask(params, rule->var);
	u64 format;

	switch (uni->tdm_slot.slot_width) {
	case 16:
		format = SNDRV_PCM_FMTBIT_S16_LE;
		break;
	case 32:
		format = SNDRV_PCM_FMTBIT_S32_LE;
		break;
	default:
		dev_err(uni->dev, "format not supported: %d bits\n",
			uni->tdm_slot.slot_width);
		return -EINVAL;
	}

	maskp->bits[0] &= (u_int32_t)format;
	maskp->bits[1] &= (u_int32_t)(format >> 32);
	/* clear remaining indexes */
	memset(maskp->bits + 2, 0, (SNDRV_MASK_MAX - 64) / 8);

	if (!maskp->bits[0] && !maskp->bits[1])
		return -EINVAL;

	return 0;
}