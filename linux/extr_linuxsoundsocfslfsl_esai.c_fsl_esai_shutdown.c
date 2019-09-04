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
struct fsl_esai {int /*<<< orphan*/  coreclk; int /*<<< orphan*/  spbaclk; int /*<<< orphan*/  extalclk; int /*<<< orphan*/  fsysclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct fsl_esai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void fsl_esai_shutdown(struct snd_pcm_substream *substream,
			      struct snd_soc_dai *dai)
{
	struct fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);

	if (!IS_ERR(esai_priv->fsysclk))
		clk_disable_unprepare(esai_priv->fsysclk);
	if (!IS_ERR(esai_priv->extalclk))
		clk_disable_unprepare(esai_priv->extalclk);
	if (!IS_ERR(esai_priv->spbaclk))
		clk_disable_unprepare(esai_priv->spbaclk);
	clk_disable_unprepare(esai_priv->coreclk);
}