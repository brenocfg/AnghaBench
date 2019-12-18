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
typedef  int u32 ;
struct madera_priv {struct madera* madera; } ;
struct madera_codec_pdata {int* out_mono; int* max_channels_clocked; int* pdm_fmt; int* pdm_mute; int* dmic_ref; } ;
struct TYPE_2__ {struct madera_codec_pdata codec; } ;
struct madera {int /*<<< orphan*/  dev; TYPE_1__ pdata; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int madera_get_variable_u32_array (int /*<<< orphan*/ ,char*,int*,int,int) ; 
 int /*<<< orphan*/  madera_prop_get_inmode (struct madera_priv*) ; 

__attribute__((used)) static void madera_prop_get_pdata(struct madera_priv *priv)
{
	struct madera *madera = priv->madera;
	struct madera_codec_pdata *pdata = &madera->pdata.codec;
	u32 out_mono[ARRAY_SIZE(pdata->out_mono)];
	int i, n;

	madera_prop_get_inmode(priv);

	n = madera_get_variable_u32_array(madera->dev, "cirrus,out-mono",
					  out_mono, ARRAY_SIZE(out_mono), 1);
	if (n > 0)
		for (i = 0; i < n; ++i)
			pdata->out_mono[i] = !!out_mono[i];

	madera_get_variable_u32_array(madera->dev,
				      "cirrus,max-channels-clocked",
				      pdata->max_channels_clocked,
				      ARRAY_SIZE(pdata->max_channels_clocked),
				      1);

	madera_get_variable_u32_array(madera->dev, "cirrus,pdm-fmt",
				      pdata->pdm_fmt,
				      ARRAY_SIZE(pdata->pdm_fmt), 1);

	madera_get_variable_u32_array(madera->dev, "cirrus,pdm-mute",
				      pdata->pdm_mute,
				      ARRAY_SIZE(pdata->pdm_mute), 1);

	madera_get_variable_u32_array(madera->dev, "cirrus,dmic-ref",
				      pdata->dmic_ref,
				      ARRAY_SIZE(pdata->dmic_ref), 1);
}