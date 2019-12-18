#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_soc_component {int dummy; } ;
struct reg_sequence {int member_0; int member_1; int /*<<< orphan*/  def; } ;
struct arizona_priv {struct arizona* arizona; } ;
struct arizona {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dac_comp_lock; int /*<<< orphan*/  dac_comp_enabled; int /*<<< orphan*/  dac_comp_coeff; } ;

/* Variables and functions */
 int ARIZONA_DAC_COMP_1 ; 
 int ARIZONA_DAC_COMP_2 ; 
 int /*<<< orphan*/  ARRAY_SIZE (struct reg_sequence*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_multi_reg_write (int /*<<< orphan*/ ,struct reg_sequence*,int /*<<< orphan*/ ) ; 
 struct arizona_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void arizona_wm5102_set_dac_comp(struct snd_soc_component *component,
					unsigned int rate)
{
	struct arizona_priv *priv = snd_soc_component_get_drvdata(component);
	struct arizona *arizona = priv->arizona;
	struct reg_sequence dac_comp[] = {
		{ 0x80, 0x3 },
		{ ARIZONA_DAC_COMP_1, 0 },
		{ ARIZONA_DAC_COMP_2, 0 },
		{ 0x80, 0x0 },
	};

	mutex_lock(&arizona->dac_comp_lock);

	dac_comp[1].def = arizona->dac_comp_coeff;
	if (rate >= 176400)
		dac_comp[2].def = arizona->dac_comp_enabled;

	mutex_unlock(&arizona->dac_comp_lock);

	regmap_multi_reg_write(arizona->regmap,
			       dac_comp,
			       ARRAY_SIZE(dac_comp));
}