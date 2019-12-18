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
struct TYPE_3__ {int* status; } ;
struct TYPE_4__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct regmap {int dummy; } ;
struct fsl_spdif_priv {struct regmap* regmap; } ;

/* Variables and functions */
 int EAGAIN ; 
 int INT_CNEW ; 
 int /*<<< orphan*/  REG_SPDIF_SIC ; 
 int /*<<< orphan*/  REG_SPDIF_SIS ; 
 int /*<<< orphan*/  REG_SPDIF_SRCSH ; 
 int /*<<< orphan*/  REG_SPDIF_SRCSL ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_dai* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct fsl_spdif_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_spdif_capture_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	struct fsl_spdif_priv *spdif_priv = snd_soc_dai_get_drvdata(cpu_dai);
	struct regmap *regmap = spdif_priv->regmap;
	u32 cstatus, val;

	regmap_read(regmap, REG_SPDIF_SIS, &val);
	if (!(val & INT_CNEW))
		return -EAGAIN;

	regmap_read(regmap, REG_SPDIF_SRCSH, &cstatus);
	ucontrol->value.iec958.status[0] = (cstatus >> 16) & 0xFF;
	ucontrol->value.iec958.status[1] = (cstatus >> 8) & 0xFF;
	ucontrol->value.iec958.status[2] = cstatus & 0xFF;

	regmap_read(regmap, REG_SPDIF_SRCSL, &cstatus);
	ucontrol->value.iec958.status[3] = (cstatus >> 16) & 0xFF;
	ucontrol->value.iec958.status[4] = (cstatus >> 8) & 0xFF;
	ucontrol->value.iec958.status[5] = cstatus & 0xFF;

	/* Clear intr */
	regmap_write(regmap, REG_SPDIF_SIC, INT_CNEW);

	return 0;
}