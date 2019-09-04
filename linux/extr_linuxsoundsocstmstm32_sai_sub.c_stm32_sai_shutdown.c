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
struct stm32_sai_sub_data {int /*<<< orphan*/ * substream; int /*<<< orphan*/  sai_ck; int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAI_XCR1_NODIV ; 
 int /*<<< orphan*/  SAI_XIMR_MASK ; 
 int /*<<< orphan*/  STM_SAI_CR1_REGX ; 
 int /*<<< orphan*/  STM_SAI_IMR_REGX ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stm32_sai_sub_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void stm32_sai_shutdown(struct snd_pcm_substream *substream,
			       struct snd_soc_dai *cpu_dai)
{
	struct stm32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);

	regmap_update_bits(sai->regmap, STM_SAI_IMR_REGX, SAI_XIMR_MASK, 0);

	regmap_update_bits(sai->regmap, STM_SAI_CR1_REGX, SAI_XCR1_NODIV,
			   SAI_XCR1_NODIV);

	clk_disable_unprepare(sai->sai_ck);
	sai->substream = NULL;
}