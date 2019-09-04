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
struct regmap {int dummy; } ;
struct fsl_spdif_priv {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SPDIF_SRCD ; 
 int SRCD_CD_USER ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 struct snd_soc_dai* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct fsl_spdif_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_spdif_usync_get(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	struct fsl_spdif_priv *spdif_priv = snd_soc_dai_get_drvdata(cpu_dai);
	struct regmap *regmap = spdif_priv->regmap;
	u32 val;

	regmap_read(regmap, REG_SPDIF_SRCD, &val);
	ucontrol->value.integer.value[0] = (val & SRCD_CD_USER) != 0;

	return 0;
}