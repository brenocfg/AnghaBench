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
struct stm32_sai_sub_data {int /*<<< orphan*/  regmap; scalar_t__ master; int /*<<< orphan*/  sai_ck; struct snd_pcm_substream* substream; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int SAI_XCLRFR_MASK ; 
 int SAI_XCR2_MUTECNT_MASK ; 
 int SAI_XIMR_AFSDETIE ; 
 int SAI_XIMR_LFSDETIE ; 
 int SAI_XIMR_MASK ; 
 int SAI_XIMR_MUTEDETIE ; 
 int SAI_XIMR_OVRUDRIE ; 
 int SAI_XIMR_WCKCFGIE ; 
 int /*<<< orphan*/  STM_SAI_CLRFR_REGX ; 
 int /*<<< orphan*/  STM_SAI_CR2_REGX ; 
 int /*<<< orphan*/  STM_SAI_IMR_REGX ; 
 scalar_t__ STM_SAI_IS_CAPTURE (struct stm32_sai_sub_data*) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct stm32_sai_sub_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int stm32_sai_startup(struct snd_pcm_substream *substream,
			     struct snd_soc_dai *cpu_dai)
{
	struct stm32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	int imr, cr2, ret;

	sai->substream = substream;

	ret = clk_prepare_enable(sai->sai_ck);
	if (ret < 0) {
		dev_err(cpu_dai->dev, "Failed to enable clock: %d\n", ret);
		return ret;
	}

	/* Enable ITs */

	regmap_update_bits(sai->regmap, STM_SAI_CLRFR_REGX,
			   SAI_XCLRFR_MASK, SAI_XCLRFR_MASK);

	imr = SAI_XIMR_OVRUDRIE;
	if (STM_SAI_IS_CAPTURE(sai)) {
		regmap_read(sai->regmap, STM_SAI_CR2_REGX, &cr2);
		if (cr2 & SAI_XCR2_MUTECNT_MASK)
			imr |= SAI_XIMR_MUTEDETIE;
	}

	if (sai->master)
		imr |= SAI_XIMR_WCKCFGIE;
	else
		imr |= SAI_XIMR_AFSDETIE | SAI_XIMR_LFSDETIE;

	regmap_update_bits(sai->regmap, STM_SAI_IMR_REGX,
			   SAI_XIMR_MASK, imr);

	return 0;
}