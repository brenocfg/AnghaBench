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
typedef  unsigned int u32 ;
struct soc_enum {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {unsigned int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct fsl_audmix {int tdms; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FSL_AUDMIX_CTR ; 
 unsigned int FSL_AUDMIX_CTR_MIXCLK_MASK ; 
 unsigned int FSL_AUDMIX_CTR_MIXCLK_SHIFT ; 
 unsigned int FSL_AUDMIX_CTR_OUTSRC (unsigned int) ; 
 unsigned int FSL_AUDMIX_CTR_OUTSRC_MASK ; 
 unsigned int FSL_AUDMIX_CTR_OUTSRC_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int fsl_audmix_state_trans (struct snd_soc_component*,unsigned int*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** prms ; 
 struct snd_soc_component* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct fsl_audmix* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int snd_soc_enum_item_to_val (struct soc_enum*,unsigned int) ; 

__attribute__((used)) static int fsl_audmix_put_out_src(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *comp = snd_kcontrol_chip(kcontrol);
	struct fsl_audmix *priv = snd_soc_component_get_drvdata(comp);
	struct soc_enum *e = (struct soc_enum *)kcontrol->private_value;
	unsigned int *item = ucontrol->value.enumerated.item;
	u32 out_src, mix_clk;
	unsigned int reg_val, val, mask = 0, ctr = 0;
	int ret = 0;

	/* Get current state */
	ret = snd_soc_component_read(comp, FSL_AUDMIX_CTR, &reg_val);
	if (ret)
		return ret;

	/* "From" state */
	out_src = ((reg_val & FSL_AUDMIX_CTR_OUTSRC_MASK)
			>> FSL_AUDMIX_CTR_OUTSRC_SHIFT);
	mix_clk = ((reg_val & FSL_AUDMIX_CTR_MIXCLK_MASK)
			>> FSL_AUDMIX_CTR_MIXCLK_SHIFT);

	/* "To" state */
	val = snd_soc_enum_item_to_val(e, item[0]);

	dev_dbg(comp->dev, "TDMs=x%08x, val=x%08x\n", priv->tdms, val);

	/* Check if state is changing ... */
	if (out_src == val)
		return 0;
	/**
	 * Ensure the current selected mixer clock is available
	 * for configuration propagation
	 */
	if (!(priv->tdms & BIT(mix_clk))) {
		dev_err(comp->dev,
			"Started TDM%d needed for config propagation!\n",
			mix_clk + 1);
		return -EINVAL;
	}

	/* Check state transition constraints */
	ret = fsl_audmix_state_trans(comp, &mask, &ctr, prms[out_src][val]);
	if (ret)
		return ret;

	/* Complete transition to new state */
	mask |= FSL_AUDMIX_CTR_OUTSRC_MASK;
	ctr  |= FSL_AUDMIX_CTR_OUTSRC(val);

	return snd_soc_component_update_bits(comp, FSL_AUDMIX_CTR, mask, ctr);
}