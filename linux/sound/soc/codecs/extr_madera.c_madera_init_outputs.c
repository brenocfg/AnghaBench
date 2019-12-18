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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct madera_priv {struct madera* madera; } ;
struct madera_codec_pdata {int* pdm_fmt; int* pdm_mute; scalar_t__* out_mono; } ;
struct TYPE_2__ {struct madera_codec_pdata codec; } ;
struct madera {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; TYPE_1__ pdata; } ;

/* Variables and functions */
 int MADERA_MAX_OUTPUT ; 
 int MADERA_MAX_PDM_SPK ; 
 unsigned int MADERA_OUT1_MONO ; 
 scalar_t__ MADERA_OUTPUT_PATH_CONFIG_1L ; 
 scalar_t__ MADERA_PDM_SPK1_CTRL_1 ; 
 scalar_t__ MADERA_PDM_SPK1_CTRL_2 ; 
 unsigned int MADERA_SPK1_FMT_MASK ; 
 unsigned int MADERA_SPK1_MUTE_ENDIAN_MASK ; 
 unsigned int MADERA_SPK1_MUTE_SEQ1_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/ * madera_mono_routes ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct madera_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ *,int) ; 

int madera_init_outputs(struct snd_soc_component *component, int n_mono_routes)
{
	struct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	struct madera_priv *priv = snd_soc_component_get_drvdata(component);
	struct madera *madera = priv->madera;
	const struct madera_codec_pdata *pdata = &madera->pdata.codec;
	unsigned int val;
	int i;

	if (n_mono_routes > MADERA_MAX_OUTPUT) {
		dev_warn(madera->dev,
			 "Requested %d mono outputs, using maximum allowed %d\n",
			 n_mono_routes, MADERA_MAX_OUTPUT);
		n_mono_routes = MADERA_MAX_OUTPUT;
	}

	for (i = 0; i < n_mono_routes; i++) {
		/* Default is 0 so noop with defaults */
		if (pdata->out_mono[i]) {
			val = MADERA_OUT1_MONO;
			snd_soc_dapm_add_routes(dapm,
						&madera_mono_routes[i], 1);
		} else {
			val = 0;
		}

		regmap_update_bits(madera->regmap,
				   MADERA_OUTPUT_PATH_CONFIG_1L + (i * 8),
				   MADERA_OUT1_MONO, val);

		dev_dbg(madera->dev, "OUT%d mono=0x%x\n", i + 1, val);
	}

	for (i = 0; i < MADERA_MAX_PDM_SPK; i++) {
		dev_dbg(madera->dev, "PDM%d fmt=0x%x mute=0x%x\n", i + 1,
			pdata->pdm_fmt[i], pdata->pdm_mute[i]);

		if (pdata->pdm_mute[i])
			regmap_update_bits(madera->regmap,
					   MADERA_PDM_SPK1_CTRL_1 + (i * 2),
					   MADERA_SPK1_MUTE_ENDIAN_MASK |
					   MADERA_SPK1_MUTE_SEQ1_MASK,
					   pdata->pdm_mute[i]);

		if (pdata->pdm_fmt[i])
			regmap_update_bits(madera->regmap,
					   MADERA_PDM_SPK1_CTRL_2 + (i * 2),
					   MADERA_SPK1_FMT_MASK,
					   pdata->pdm_fmt[i]);
	}

	return 0;
}