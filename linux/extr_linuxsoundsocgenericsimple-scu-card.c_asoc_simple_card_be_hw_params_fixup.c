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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct simple_card_data {int /*<<< orphan*/  adata; } ;

/* Variables and functions */
 int /*<<< orphan*/  asoc_simple_card_convert_fixup (int /*<<< orphan*/ *,struct snd_pcm_hw_params*) ; 
 struct simple_card_data* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asoc_simple_card_be_hw_params_fixup(struct snd_soc_pcm_runtime *rtd,
					struct snd_pcm_hw_params *params)
{
	struct simple_card_data *priv = snd_soc_card_get_drvdata(rtd->card);

	asoc_simple_card_convert_fixup(&priv->adata, params);

	return 0;
}