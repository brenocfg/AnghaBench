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
struct snd_soc_pcm_runtime {struct snd_soc_card* card; } ;
struct snd_soc_card_drvdata_davinci {scalar_t__ mclk; } ;
struct snd_soc_card {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 struct snd_soc_card_drvdata_davinci* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static void evm_shutdown(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_card *soc_card = rtd->card;
	struct snd_soc_card_drvdata_davinci *drvdata =
		snd_soc_card_get_drvdata(soc_card);

	if (drvdata->mclk)
		clk_disable_unprepare(drvdata->mclk);
}