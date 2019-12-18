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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  num; int /*<<< orphan*/  card; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct simple_dai_props {int /*<<< orphan*/  adata; } ;
struct asoc_simple_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asoc_simple_convert_fixup (int /*<<< orphan*/ *,struct snd_pcm_hw_params*) ; 
 struct simple_dai_props* simple_priv_to_props (struct asoc_simple_priv*,int /*<<< orphan*/ ) ; 
 struct asoc_simple_priv* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

int asoc_simple_be_hw_params_fixup(struct snd_soc_pcm_runtime *rtd,
				   struct snd_pcm_hw_params *params)
{
	struct asoc_simple_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	struct simple_dai_props *dai_props = simple_priv_to_props(priv, rtd->num);

	asoc_simple_convert_fixup(&dai_props->adata, params);

	return 0;
}