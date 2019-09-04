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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct es7134_data {int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int es7134_check_mclk (struct snd_soc_dai*,struct es7134_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 struct es7134_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int es7134_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct es7134_data *priv = snd_soc_dai_get_drvdata(dai);

	/* mclk has not been provided, assume it is OK */
	if (!priv->mclk)
		return 0;

	return es7134_check_mclk(dai, priv, params_rate(params));
}