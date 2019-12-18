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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct xlnx_pcm_stream_param {int ch_limit; scalar_t__ xfer_mode; scalar_t__ mmio; int /*<<< orphan*/  buffer_size; } ;
struct snd_soc_pcm_runtime {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct snd_pcm_substream {scalar_t__ stream; TYPE_1__ dma_buffer; struct snd_pcm_runtime* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_runtime {struct xlnx_pcm_stream_param* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 scalar_t__ AES_TO_PCM ; 
 int AUD_CTRL_ACTIVE_CH_SHIFT ; 
 int AUD_CTRL_DATA_WIDTH_SHIFT ; 
 int AUD_STS_CH_STS_MASK ; 
 int BIT_DEPTH_16 ; 
 int BIT_DEPTH_20 ; 
 int BIT_DEPTH_24 ; 
 int BIT_DEPTH_32 ; 
 int BIT_DEPTH_8 ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int PERIOD_CFG_PERIODS_SHIFT ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 scalar_t__ XLNX_AUD_BUFF_ADDR_LSB ; 
 scalar_t__ XLNX_AUD_BUFF_ADDR_MSB ; 
 scalar_t__ XLNX_AUD_CH_STS_START ; 
 scalar_t__ XLNX_AUD_CTRL ; 
 scalar_t__ XLNX_AUD_PERIOD_CONFIG ; 
 scalar_t__ XLNX_AUD_STS ; 
 scalar_t__ XLNX_BYTES_PER_CH ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_period_bytes (struct snd_pcm_hw_params*) ; 
 int params_periods (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int readl (scalar_t__) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  xlnx_parse_aes_params (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlnx_formatter_pcm_hw_params(struct snd_pcm_substream *substream,
					struct snd_pcm_hw_params *params)
{
	u32 low, high, active_ch, val, bytes_per_ch, bits_per_sample;
	u32 aes_reg1_val, aes_reg2_val;
	int status;
	u64 size;
	struct snd_soc_pcm_runtime *prtd = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(prtd,
								    DRV_NAME);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct xlnx_pcm_stream_param *stream_data = runtime->private_data;

	active_ch = params_channels(params);
	if (active_ch > stream_data->ch_limit)
		return -EINVAL;

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE &&
	    stream_data->xfer_mode == AES_TO_PCM) {
		val = readl(stream_data->mmio + XLNX_AUD_STS);
		if (val & AUD_STS_CH_STS_MASK) {
			aes_reg1_val = readl(stream_data->mmio +
					     XLNX_AUD_CH_STS_START);
			aes_reg2_val = readl(stream_data->mmio +
					     XLNX_AUD_CH_STS_START + 0x4);

			xlnx_parse_aes_params(aes_reg1_val, aes_reg2_val,
					      component->dev);
		}
	}

	size = params_buffer_bytes(params);
	status = snd_pcm_lib_malloc_pages(substream, size);
	if (status < 0)
		return status;

	stream_data->buffer_size = size;

	low = lower_32_bits(substream->dma_buffer.addr);
	high = upper_32_bits(substream->dma_buffer.addr);
	writel(low, stream_data->mmio + XLNX_AUD_BUFF_ADDR_LSB);
	writel(high, stream_data->mmio + XLNX_AUD_BUFF_ADDR_MSB);

	val = readl(stream_data->mmio + XLNX_AUD_CTRL);
	bits_per_sample = params_width(params);
	switch (bits_per_sample) {
	case 8:
		val |= (BIT_DEPTH_8 << AUD_CTRL_DATA_WIDTH_SHIFT);
		break;
	case 16:
		val |= (BIT_DEPTH_16 << AUD_CTRL_DATA_WIDTH_SHIFT);
		break;
	case 20:
		val |= (BIT_DEPTH_20 << AUD_CTRL_DATA_WIDTH_SHIFT);
		break;
	case 24:
		val |= (BIT_DEPTH_24 << AUD_CTRL_DATA_WIDTH_SHIFT);
		break;
	case 32:
		val |= (BIT_DEPTH_32 << AUD_CTRL_DATA_WIDTH_SHIFT);
		break;
	default:
		return -EINVAL;
	}

	val |= active_ch << AUD_CTRL_ACTIVE_CH_SHIFT;
	writel(val, stream_data->mmio + XLNX_AUD_CTRL);

	val = (params_periods(params) << PERIOD_CFG_PERIODS_SHIFT)
		| params_period_bytes(params);
	writel(val, stream_data->mmio + XLNX_AUD_PERIOD_CONFIG);
	bytes_per_ch = DIV_ROUND_UP(params_period_bytes(params), active_ch);
	writel(bytes_per_ch, stream_data->mmio + XLNX_BYTES_PER_CH);

	return 0;
}