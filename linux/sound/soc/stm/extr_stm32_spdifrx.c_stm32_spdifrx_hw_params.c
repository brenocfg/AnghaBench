#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  addr_width; } ;
struct stm32_spdifrx_data {int /*<<< orphan*/  regmap; TYPE_2__ dma_params; TYPE_1__* pdev; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EINVAL ; 
 int /*<<< orphan*/  SPDIFRX_CR_DRFMTSET (int) ; 
 int /*<<< orphan*/  SPDIFRX_CR_DRFMT_MASK ; 
 int SPDIFRX_DRFMT_LEFT ; 
 int SPDIFRX_DRFMT_PACKED ; 
 int /*<<< orphan*/  STM32_SPDIFRX_CR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stm32_spdifrx_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int stm32_spdifrx_hw_params(struct snd_pcm_substream *substream,
				   struct snd_pcm_hw_params *params,
				   struct snd_soc_dai *cpu_dai)
{
	struct stm32_spdifrx_data *spdifrx = snd_soc_dai_get_drvdata(cpu_dai);
	int data_size = params_width(params);
	int fmt;

	switch (data_size) {
	case 16:
		fmt = SPDIFRX_DRFMT_PACKED;
		break;
	case 32:
		fmt = SPDIFRX_DRFMT_LEFT;
		break;
	default:
		dev_err(&spdifrx->pdev->dev, "Unexpected data format\n");
		return -EINVAL;
	}

	/*
	 * Set buswidth to 4 bytes for all data formats.
	 * Packed format: transfer 2 x 2 bytes samples
	 * Left format: transfer 1 x 3 bytes samples + 1 dummy byte
	 */
	spdifrx->dma_params.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	snd_soc_dai_init_dma_data(cpu_dai, NULL, &spdifrx->dma_params);

	return regmap_update_bits(spdifrx->regmap, STM32_SPDIFRX_CR,
				  SPDIFRX_CR_DRFMT_MASK,
				  SPDIFRX_CR_DRFMTSET(fmt));
}