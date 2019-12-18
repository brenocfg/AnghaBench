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
typedef  int u8 ;
struct soc_bytes_ext {int max; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int* data; } ;
struct TYPE_4__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct da7218_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/  stbiq_3stage_coeff; int /*<<< orphan*/  biq_5stage_coeff; } ;

/* Variables and functions */
 size_t DA7218_BIQ_CFG_ADDR ; 
 size_t DA7218_BIQ_CFG_DATA ; 
 int DA7218_BIQ_CFG_SIZE ; 
 int /*<<< orphan*/  DA7218_OUT_1L_FILTER_CTRL ; 
 int DA7218_OUT_1L_FILTER_EN_MASK ; 
#define  DA7218_OUT_1_BIQ_5STAGE_CFG_SIZE 129 
 int DA7218_OUT_1_BIQ_5STAGE_DATA ; 
#define  DA7218_SIDETONE_BIQ_3STAGE_CFG_SIZE 128 
 int DA7218_SIDETONE_BIQ_3STAGE_DATA ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  regmap_raw_write (int /*<<< orphan*/ ,int,int*,int) ; 
 struct da7218_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int da7218_biquad_coeff_put(struct snd_kcontrol *kcontrol,
				   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	struct soc_bytes_ext *bytes_ext =
		(struct soc_bytes_ext *) kcontrol->private_value;
	u8 reg, out_filt1l;
	u8 cfg[DA7218_BIQ_CFG_SIZE];
	int i;

	/*
	 * Determine which BiQuads we're setting based on size of config data,
	 * and stored the data for use by get function.
	 */
	switch (bytes_ext->max) {
	case DA7218_OUT_1_BIQ_5STAGE_CFG_SIZE:
		reg = DA7218_OUT_1_BIQ_5STAGE_DATA;
		memcpy(da7218->biq_5stage_coeff, ucontrol->value.bytes.data,
		       bytes_ext->max);
		break;
	case DA7218_SIDETONE_BIQ_3STAGE_CFG_SIZE:
		reg = DA7218_SIDETONE_BIQ_3STAGE_DATA;
		memcpy(da7218->stbiq_3stage_coeff, ucontrol->value.bytes.data,
		       bytes_ext->max);
		break;
	default:
		return -EINVAL;
	}

	/* Make sure at least out filter1 enabled to allow programming */
	out_filt1l = snd_soc_component_read32(component, DA7218_OUT_1L_FILTER_CTRL);
	snd_soc_component_write(component, DA7218_OUT_1L_FILTER_CTRL,
		      out_filt1l | DA7218_OUT_1L_FILTER_EN_MASK);

	for (i = 0; i < bytes_ext->max; ++i) {
		cfg[DA7218_BIQ_CFG_DATA] = ucontrol->value.bytes.data[i];
		cfg[DA7218_BIQ_CFG_ADDR] = i;
		regmap_raw_write(da7218->regmap, reg, cfg, DA7218_BIQ_CFG_SIZE);
	}

	/* Restore filter to previous setting */
	snd_soc_component_write(component, DA7218_OUT_1L_FILTER_CTRL, out_filt1l);

	return 0;
}