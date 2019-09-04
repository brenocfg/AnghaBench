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
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct atmel_pdmic {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDMIC_CDR ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct atmel_pdmic* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_pdmic_cpu_dai_prepare(struct snd_pcm_substream *substream,
					struct snd_soc_dai *cpu_dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct atmel_pdmic *dd = snd_soc_card_get_drvdata(rtd->card);
	u32 val;

	/* Clean the PDMIC Converted Data Register */
	return regmap_read(dd->regmap, PDMIC_CDR, &val);
}