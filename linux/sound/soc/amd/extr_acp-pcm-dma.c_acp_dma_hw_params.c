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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_pcm_runtime {struct snd_soc_card* card; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_soc_card {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; scalar_t__ area; } ;
struct snd_pcm_substream {scalar_t__ stream; TYPE_1__ dma_buffer; struct snd_pcm_runtime* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  dma_area; struct audio_substream_data* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct audio_substream_data {int i2s_instance; int num_of_pages; scalar_t__ direction; int /*<<< orphan*/  acp_mmio; int /*<<< orphan*/  size; int /*<<< orphan*/  order; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  dma_curr_dscr; int /*<<< orphan*/  byte_cnt_low_reg_offset; int /*<<< orphan*/  byte_cnt_high_reg_offset; int /*<<< orphan*/  dma_dscr_idx_2; int /*<<< orphan*/  dma_dscr_idx_1; int /*<<< orphan*/  destination; int /*<<< orphan*/  sram_bank; void* pte_offset; int /*<<< orphan*/  ch2; int /*<<< orphan*/  ch1; int /*<<< orphan*/  capture_channel; } ;
struct audio_drv_data {scalar_t__ asic_type; struct snd_pcm_substream* capture_i2ssp_stream; struct snd_pcm_substream* capture_i2sbt_stream; struct snd_pcm_substream* play_i2ssp_stream; struct snd_pcm_substream* play_i2sbt_stream; int /*<<< orphan*/  acp_mmio; } ;
struct acp_platform_info {int play_i2s_instance; int cap_i2s_instance; int /*<<< orphan*/  capture_channel; } ;

/* Variables and functions */
 void* ACP_CAPTURE_PTE_OFFSET ; 
 int /*<<< orphan*/  ACP_I2S_BT_16BIT_RESOLUTION_EN ; 
 int /*<<< orphan*/  ACP_I2S_MIC_16BIT_RESOLUTION_EN ; 
 int /*<<< orphan*/  ACP_I2S_SP_16BIT_RESOLUTION_EN ; 
 void* ACP_PLAYBACK_PTE_OFFSET ; 
 int /*<<< orphan*/  ACP_SRAM_BANK_1_ADDRESS ; 
 int /*<<< orphan*/  ACP_SRAM_BANK_2_ADDRESS ; 
 int /*<<< orphan*/  ACP_SRAM_BANK_3_ADDRESS ; 
 int /*<<< orphan*/  ACP_SRAM_BANK_4_ADDRESS ; 
 int /*<<< orphan*/  ACP_SRAM_BANK_5_ADDRESS ; 
 void* ACP_ST_BT_CAPTURE_PTE_OFFSET ; 
 void* ACP_ST_BT_PLAYBACK_PTE_OFFSET ; 
 void* ACP_ST_CAPTURE_PTE_OFFSET ; 
 void* ACP_ST_PLAYBACK_PTE_OFFSET ; 
 int /*<<< orphan*/  ACP_TO_I2S_DMA_BT_INSTANCE_CH_NUM ; 
 int /*<<< orphan*/  ACP_TO_I2S_DMA_CH_NUM ; 
 int /*<<< orphan*/  ACP_TO_SYSRAM_BT_INSTANCE_CH_NUM ; 
 int /*<<< orphan*/  ACP_TO_SYSRAM_CH_NUM ; 
 int /*<<< orphan*/  CAPTURE_START_DMA_DESCR_CH10 ; 
 int /*<<< orphan*/  CAPTURE_START_DMA_DESCR_CH11 ; 
 int /*<<< orphan*/  CAPTURE_START_DMA_DESCR_CH14 ; 
 int /*<<< orphan*/  CAPTURE_START_DMA_DESCR_CH15 ; 
#define  CHIP_STONEY 130 
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FROM_ACP_I2S_1 ; 
 int /*<<< orphan*/  FROM_BLUETOOTH ; 
#define  I2S_BT_INSTANCE 129 
#define  I2S_SP_INSTANCE 128 
 int /*<<< orphan*/  I2S_TO_ACP_DMA_BT_INSTANCE_CH_NUM ; 
 int /*<<< orphan*/  I2S_TO_ACP_DMA_CH_NUM ; 
 int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PLAYBACK_START_DMA_DESCR_CH12 ; 
 int /*<<< orphan*/  PLAYBACK_START_DMA_DESCR_CH13 ; 
 int /*<<< orphan*/  PLAYBACK_START_DMA_DESCR_CH8 ; 
 int /*<<< orphan*/  PLAYBACK_START_DMA_DESCR_CH9 ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SYSRAM_TO_ACP_BT_INSTANCE_CH_NUM ; 
 int /*<<< orphan*/  SYSRAM_TO_ACP_CH_NUM ; 
 int /*<<< orphan*/  TO_ACP_I2S_1 ; 
 int /*<<< orphan*/  TO_BLUETOOTH ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  acp_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acp_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acp_set_sram_bank_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  config_acp_dma (int /*<<< orphan*/ ,struct audio_substream_data*,scalar_t__) ; 
 struct audio_drv_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmACP_DMA_CUR_DSCR_11 ; 
 int /*<<< orphan*/  mmACP_DMA_CUR_DSCR_15 ; 
 int /*<<< orphan*/  mmACP_I2S_16BIT_RESOLUTION_EN ; 
 int /*<<< orphan*/  mmACP_I2S_BT_RECEIVE_BYTE_CNT_HIGH ; 
 int /*<<< orphan*/  mmACP_I2S_BT_RECEIVE_BYTE_CNT_LOW ; 
 int /*<<< orphan*/  mmACP_I2S_BT_TRANSMIT_BYTE_CNT_HIGH ; 
 int /*<<< orphan*/  mmACP_I2S_BT_TRANSMIT_BYTE_CNT_LOW ; 
 int /*<<< orphan*/  mmACP_I2S_RECEIVED_BYTE_CNT_HIGH ; 
 int /*<<< orphan*/  mmACP_I2S_RECEIVED_BYTE_CNT_LOW ; 
 int /*<<< orphan*/  mmACP_I2S_TRANSMIT_BYTE_CNT_HIGH ; 
 int /*<<< orphan*/  mmACP_I2S_TRANSMIT_BYTE_CNT_LOW ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct acp_platform_info* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acp_dma_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params)
{
	int status;
	uint64_t size;
	u32 val = 0;
	struct snd_pcm_runtime *runtime;
	struct audio_substream_data *rtd;
	struct snd_soc_pcm_runtime *prtd = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(prtd,
								    DRV_NAME);
	struct audio_drv_data *adata = dev_get_drvdata(component->dev);
	struct snd_soc_card *card = prtd->card;
	struct acp_platform_info *pinfo = snd_soc_card_get_drvdata(card);

	runtime = substream->runtime;
	rtd = runtime->private_data;

	if (WARN_ON(!rtd))
		return -EINVAL;

	if (pinfo) {
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
			rtd->i2s_instance = pinfo->play_i2s_instance;
		} else {
			rtd->i2s_instance = pinfo->cap_i2s_instance;
			rtd->capture_channel = pinfo->capture_channel;
		}
	}
	if (adata->asic_type == CHIP_STONEY) {
		val = acp_reg_read(adata->acp_mmio,
				   mmACP_I2S_16BIT_RESOLUTION_EN);
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
			switch (rtd->i2s_instance) {
			case I2S_BT_INSTANCE:
				val |= ACP_I2S_BT_16BIT_RESOLUTION_EN;
				break;
			case I2S_SP_INSTANCE:
			default:
				val |= ACP_I2S_SP_16BIT_RESOLUTION_EN;
			}
		} else {
			switch (rtd->i2s_instance) {
			case I2S_BT_INSTANCE:
				val |= ACP_I2S_BT_16BIT_RESOLUTION_EN;
				break;
			case I2S_SP_INSTANCE:
			default:
				val |= ACP_I2S_MIC_16BIT_RESOLUTION_EN;
			}
		}
		acp_reg_write(val, adata->acp_mmio,
			      mmACP_I2S_16BIT_RESOLUTION_EN);
	}

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		switch (rtd->i2s_instance) {
		case I2S_BT_INSTANCE:
			rtd->pte_offset = ACP_ST_BT_PLAYBACK_PTE_OFFSET;
			rtd->ch1 = SYSRAM_TO_ACP_BT_INSTANCE_CH_NUM;
			rtd->ch2 = ACP_TO_I2S_DMA_BT_INSTANCE_CH_NUM;
			rtd->sram_bank = ACP_SRAM_BANK_3_ADDRESS;
			rtd->destination = TO_BLUETOOTH;
			rtd->dma_dscr_idx_1 = PLAYBACK_START_DMA_DESCR_CH8;
			rtd->dma_dscr_idx_2 = PLAYBACK_START_DMA_DESCR_CH9;
			rtd->byte_cnt_high_reg_offset =
					mmACP_I2S_BT_TRANSMIT_BYTE_CNT_HIGH;
			rtd->byte_cnt_low_reg_offset =
					mmACP_I2S_BT_TRANSMIT_BYTE_CNT_LOW;
			adata->play_i2sbt_stream = substream;
			break;
		case I2S_SP_INSTANCE:
		default:
			switch (adata->asic_type) {
			case CHIP_STONEY:
				rtd->pte_offset = ACP_ST_PLAYBACK_PTE_OFFSET;
				break;
			default:
				rtd->pte_offset = ACP_PLAYBACK_PTE_OFFSET;
			}
			rtd->ch1 = SYSRAM_TO_ACP_CH_NUM;
			rtd->ch2 = ACP_TO_I2S_DMA_CH_NUM;
			rtd->sram_bank = ACP_SRAM_BANK_1_ADDRESS;
			rtd->destination = TO_ACP_I2S_1;
			rtd->dma_dscr_idx_1 = PLAYBACK_START_DMA_DESCR_CH12;
			rtd->dma_dscr_idx_2 = PLAYBACK_START_DMA_DESCR_CH13;
			rtd->byte_cnt_high_reg_offset =
					mmACP_I2S_TRANSMIT_BYTE_CNT_HIGH;
			rtd->byte_cnt_low_reg_offset =
					mmACP_I2S_TRANSMIT_BYTE_CNT_LOW;
			adata->play_i2ssp_stream = substream;
		}
	} else {
		switch (rtd->i2s_instance) {
		case I2S_BT_INSTANCE:
			rtd->pte_offset = ACP_ST_BT_CAPTURE_PTE_OFFSET;
			rtd->ch1 = I2S_TO_ACP_DMA_BT_INSTANCE_CH_NUM;
			rtd->ch2 = ACP_TO_SYSRAM_BT_INSTANCE_CH_NUM;
			rtd->sram_bank = ACP_SRAM_BANK_4_ADDRESS;
			rtd->destination = FROM_BLUETOOTH;
			rtd->dma_dscr_idx_1 = CAPTURE_START_DMA_DESCR_CH10;
			rtd->dma_dscr_idx_2 = CAPTURE_START_DMA_DESCR_CH11;
			rtd->byte_cnt_high_reg_offset =
					mmACP_I2S_BT_RECEIVE_BYTE_CNT_HIGH;
			rtd->byte_cnt_low_reg_offset =
					mmACP_I2S_BT_RECEIVE_BYTE_CNT_LOW;
			rtd->dma_curr_dscr = mmACP_DMA_CUR_DSCR_11;
			adata->capture_i2sbt_stream = substream;
			break;
		case I2S_SP_INSTANCE:
		default:
			rtd->pte_offset = ACP_CAPTURE_PTE_OFFSET;
			rtd->ch1 = I2S_TO_ACP_DMA_CH_NUM;
			rtd->ch2 = ACP_TO_SYSRAM_CH_NUM;
			switch (adata->asic_type) {
			case CHIP_STONEY:
				rtd->pte_offset = ACP_ST_CAPTURE_PTE_OFFSET;
				rtd->sram_bank = ACP_SRAM_BANK_2_ADDRESS;
				break;
			default:
				rtd->pte_offset = ACP_CAPTURE_PTE_OFFSET;
				rtd->sram_bank = ACP_SRAM_BANK_5_ADDRESS;
			}
			rtd->destination = FROM_ACP_I2S_1;
			rtd->dma_dscr_idx_1 = CAPTURE_START_DMA_DESCR_CH14;
			rtd->dma_dscr_idx_2 = CAPTURE_START_DMA_DESCR_CH15;
			rtd->byte_cnt_high_reg_offset =
					mmACP_I2S_RECEIVED_BYTE_CNT_HIGH;
			rtd->byte_cnt_low_reg_offset =
					mmACP_I2S_RECEIVED_BYTE_CNT_LOW;
			rtd->dma_curr_dscr = mmACP_DMA_CUR_DSCR_15;
			adata->capture_i2ssp_stream = substream;
		}
	}

	size = params_buffer_bytes(params);
	status = snd_pcm_lib_malloc_pages(substream, size);
	if (status < 0)
		return status;

	memset(substream->runtime->dma_area, 0, params_buffer_bytes(params));

	if (substream->dma_buffer.area) {
		acp_set_sram_bank_state(rtd->acp_mmio, 0, true);
		/* Save for runtime private data */
		rtd->dma_addr = substream->dma_buffer.addr;
		rtd->order = get_order(size);

		/* Fill the page table entries in ACP SRAM */
		rtd->size = size;
		rtd->num_of_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;
		rtd->direction = substream->stream;

		config_acp_dma(rtd->acp_mmio, rtd, adata->asic_type);
		status = 0;
	} else {
		status = -ENOMEM;
	}
	return status;
}