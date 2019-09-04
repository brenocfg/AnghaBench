#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {TYPE_3__* dev; } ;
struct pm8916_wcd_analog_priv {struct snd_soc_component* component; void* codec_version; void* pmic_rev; TYPE_1__* supplies; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct TYPE_7__ {int def; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CDC_A_PERPH_RESET_CTL4 ; 
 int /*<<< orphan*/  CDC_D_CDC_RST_CTL ; 
 int /*<<< orphan*/  CDC_D_PERPH_RESET_CTL4 ; 
 int /*<<< orphan*/  CDC_D_PERPH_SUBTYPE ; 
 int /*<<< orphan*/  CDC_D_REVISION1 ; 
 int /*<<< orphan*/  RST_CTL_DIG_SW_RST_N_MASK ; 
 int /*<<< orphan*/  RST_CTL_DIG_SW_RST_N_REMOVE_RESET ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 struct pm8916_wcd_analog_priv* dev_get_drvdata (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,void*,void*) ; 
 int /*<<< orphan*/  pm8916_wcd_setup_mbhc (struct pm8916_wcd_analog_priv*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 
 int /*<<< orphan*/  snd_soc_component_init_regmap (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 void* snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_set_drvdata (struct snd_soc_component*,struct pm8916_wcd_analog_priv*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* wcd_reg_defaults_2_0 ; 

__attribute__((used)) static int pm8916_wcd_analog_probe(struct snd_soc_component *component)
{
	struct pm8916_wcd_analog_priv *priv = dev_get_drvdata(component->dev);
	int err, reg;

	err = regulator_bulk_enable(ARRAY_SIZE(priv->supplies), priv->supplies);
	if (err != 0) {
		dev_err(component->dev, "failed to enable regulators (%d)\n", err);
		return err;
	}

	snd_soc_component_init_regmap(component,
				  dev_get_regmap(component->dev->parent, NULL));
	snd_soc_component_set_drvdata(component, priv);
	priv->pmic_rev = snd_soc_component_read32(component, CDC_D_REVISION1);
	priv->codec_version = snd_soc_component_read32(component, CDC_D_PERPH_SUBTYPE);

	dev_info(component->dev, "PMIC REV: %d\t CODEC Version: %d\n",
		 priv->pmic_rev, priv->codec_version);

	snd_soc_component_write(component, CDC_D_PERPH_RESET_CTL4, 0x01);
	snd_soc_component_write(component, CDC_A_PERPH_RESET_CTL4, 0x01);

	for (reg = 0; reg < ARRAY_SIZE(wcd_reg_defaults_2_0); reg++)
		snd_soc_component_write(component, wcd_reg_defaults_2_0[reg].reg,
			      wcd_reg_defaults_2_0[reg].def);

	priv->component = component;

	snd_soc_component_update_bits(component, CDC_D_CDC_RST_CTL,
			    RST_CTL_DIG_SW_RST_N_MASK,
			    RST_CTL_DIG_SW_RST_N_REMOVE_RESET);

	pm8916_wcd_setup_mbhc(priv);

	return 0;
}