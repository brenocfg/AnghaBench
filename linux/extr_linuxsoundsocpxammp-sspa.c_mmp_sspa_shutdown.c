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
struct sspa_priv {int /*<<< orphan*/  sysclk; TYPE_1__* sspa; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct sspa_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void mmp_sspa_shutdown(struct snd_pcm_substream *substream,
	struct snd_soc_dai *dai)
{
	struct sspa_priv *priv = snd_soc_dai_get_drvdata(dai);

	clk_disable(priv->sspa->clk);
	clk_disable(priv->sysclk);

}