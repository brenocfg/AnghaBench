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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct atmel_pdmic {int /*<<< orphan*/  pclk; int /*<<< orphan*/  gclk; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDMIC_IDR ; 
 int /*<<< orphan*/  PDMIC_IDR_OVRE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atmel_pdmic* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_pdmic_cpu_dai_shutdown(struct snd_pcm_substream *substream,
					struct snd_soc_dai *cpu_dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct atmel_pdmic *dd = snd_soc_card_get_drvdata(rtd->card);

	/* Disable the overrun error interrupt */
	regmap_write(dd->regmap, PDMIC_IDR, PDMIC_IDR_OVRE);

	clk_disable_unprepare(dd->gclk);
	clk_disable_unprepare(dd->pclk);
}