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
struct snd_soc_dai {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct fsl_spdif_priv {scalar_t__ dpll_locked; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPDIF_DEFAULT_GAINSEL ; 
 struct snd_soc_dai* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct fsl_spdif_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int spdif_get_rxclk_rate (struct fsl_spdif_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_spdif_rxrate_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	struct fsl_spdif_priv *spdif_priv = snd_soc_dai_get_drvdata(cpu_dai);
	int rate = 0;

	if (spdif_priv->dpll_locked)
		rate = spdif_get_rxclk_rate(spdif_priv, SPDIF_DEFAULT_GAINSEL);

	ucontrol->value.integer.value[0] = rate;

	return 0;
}