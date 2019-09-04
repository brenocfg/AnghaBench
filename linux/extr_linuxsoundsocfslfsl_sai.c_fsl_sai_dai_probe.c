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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct fsl_sai {int /*<<< orphan*/  dma_params_rx; int /*<<< orphan*/  dma_params_tx; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSL_SAI_CR1_RFW_MASK ; 
 int /*<<< orphan*/  FSL_SAI_CSR_SR ; 
 int FSL_SAI_MAXBURST_RX ; 
 int FSL_SAI_MAXBURST_TX ; 
 int /*<<< orphan*/  FSL_SAI_RCR1 ; 
 int /*<<< orphan*/  FSL_SAI_RCSR ; 
 int /*<<< orphan*/  FSL_SAI_TCR1 ; 
 int /*<<< orphan*/  FSL_SAI_TCSR ; 
 struct fsl_sai* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_dai_set_drvdata (struct snd_soc_dai*,struct fsl_sai*) ; 

__attribute__((used)) static int fsl_sai_dai_probe(struct snd_soc_dai *cpu_dai)
{
	struct fsl_sai *sai = dev_get_drvdata(cpu_dai->dev);

	/* Software Reset for both Tx and Rx */
	regmap_write(sai->regmap, FSL_SAI_TCSR, FSL_SAI_CSR_SR);
	regmap_write(sai->regmap, FSL_SAI_RCSR, FSL_SAI_CSR_SR);
	/* Clear SR bit to finish the reset */
	regmap_write(sai->regmap, FSL_SAI_TCSR, 0);
	regmap_write(sai->regmap, FSL_SAI_RCSR, 0);

	regmap_update_bits(sai->regmap, FSL_SAI_TCR1, FSL_SAI_CR1_RFW_MASK,
			   FSL_SAI_MAXBURST_TX * 2);
	regmap_update_bits(sai->regmap, FSL_SAI_RCR1, FSL_SAI_CR1_RFW_MASK,
			   FSL_SAI_MAXBURST_RX - 1);

	snd_soc_dai_init_dma_data(cpu_dai, &sai->dma_params_tx,
				&sai->dma_params_rx);

	snd_soc_dai_set_drvdata(cpu_dai, sai);

	return 0;
}