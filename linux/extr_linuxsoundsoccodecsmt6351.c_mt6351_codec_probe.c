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
struct mt6351_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt6351_codec_init_reg (struct snd_soc_component*) ; 
 struct mt6351_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_init_regmap (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt6351_codec_probe(struct snd_soc_component *cmpnt)
{
	struct mt6351_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	snd_soc_component_init_regmap(cmpnt, priv->regmap);

	mt6351_codec_init_reg(cmpnt);
	return 0;
}