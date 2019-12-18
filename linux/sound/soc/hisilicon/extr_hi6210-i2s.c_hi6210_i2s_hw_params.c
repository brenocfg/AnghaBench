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
typedef  int u32 ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_dmaengine_dai_dma_data {int addr_width; int maxburst; scalar_t__ addr; } ;
struct hi6210_i2s {int bits; int rate; int channels; int channel_length; int format; int master; scalar_t__ base_phys; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int HII2S_BITS_16 ; 
#define  HII2S_BITS_24 137 
 int /*<<< orphan*/  HII2S_CLK_SEL ; 
 int HII2S_CLK_SEL__EXT_12_288MHZ_SEL ; 
 int HII2S_CLK_SEL__I2S_BT_FM_SEL ; 
 int /*<<< orphan*/  HII2S_DIG_FILTER_CLK_EN_CFG ; 
 int HII2S_DIG_FILTER_CLK_EN_CFG__DACL_AGC_EN ; 
 int HII2S_DIG_FILTER_CLK_EN_CFG__DACL_HBF2I_EN ; 
 int HII2S_DIG_FILTER_CLK_EN_CFG__DACL_MIXER_EN ; 
 int HII2S_DIG_FILTER_CLK_EN_CFG__DACL_SDM_EN ; 
 int HII2S_DIG_FILTER_CLK_EN_CFG__DACR_AGC_EN ; 
 int HII2S_DIG_FILTER_CLK_EN_CFG__DACR_HBF2I_EN ; 
 int HII2S_DIG_FILTER_CLK_EN_CFG__DACR_MIXER_EN ; 
 int HII2S_DIG_FILTER_CLK_EN_CFG__DACR_SDM_EN ; 
 int /*<<< orphan*/  HII2S_DIG_FILTER_MODULE_CFG ; 
 int HII2S_DIG_FILTER_MODULE_CFG__DACL_MIXER_IN2_MUTE ; 
 int HII2S_DIG_FILTER_MODULE_CFG__DACR_MIXER_IN2_MUTE ; 
 int HII2S_FORMAT_I2S ; 
 int HII2S_FORMAT_LEFT_JUST ; 
 int HII2S_FORMAT_RIGHT_JUST ; 
 int /*<<< orphan*/  HII2S_FS_CFG ; 
 int HII2S_FS_CFG__FS_DACLR_MASK ; 
 int HII2S_FS_CFG__FS_DACLR_SHIFT ; 
 int HII2S_FS_CFG__FS_S2_MASK ; 
 int HII2S_FS_CFG__FS_S2_SHIFT ; 
 int HII2S_FS_CFG__FS_ST_DL_L_MASK ; 
 int HII2S_FS_CFG__FS_ST_DL_L_SHIFT ; 
 int HII2S_FS_CFG__FS_ST_DL_R_MASK ; 
 int HII2S_FS_CFG__FS_ST_DL_R_SHIFT ; 
 int HII2S_FS_RATE_16KHZ ; 
 int HII2S_FS_RATE_192KHZ ; 
 int HII2S_FS_RATE_32KHZ ; 
 int HII2S_FS_RATE_48KHZ ; 
 int HII2S_FS_RATE_8KHZ ; 
 int HII2S_FS_RATE_96KHZ ; 
 int /*<<< orphan*/  HII2S_I2S_CFG ; 
 int HII2S_I2S_CFG__S2_CODEC_DATA_FORMAT ; 
 int HII2S_I2S_CFG__S2_CODEC_IO_WORDLENGTH_MASK ; 
 int HII2S_I2S_CFG__S2_CODEC_IO_WORDLENGTH_SHIFT ; 
 int HII2S_I2S_CFG__S2_DIRECT_LOOP_MASK ; 
 int HII2S_I2S_CFG__S2_DIRECT_LOOP_SHIFT ; 
 int HII2S_I2S_CFG__S2_FRAME_MODE ; 
 int HII2S_I2S_CFG__S2_FUNC_MODE_MASK ; 
 int HII2S_I2S_CFG__S2_FUNC_MODE_SHIFT ; 
 int HII2S_I2S_CFG__S2_MST_SLV ; 
 int /*<<< orphan*/  HII2S_IF_CLK_EN_CFG ; 
 int HII2S_IF_CLK_EN_CFG__S2_IF_CLK_EN ; 
 int HII2S_IF_CLK_EN_CFG__S2_OL_MIXER_EN ; 
 int HII2S_IF_CLK_EN_CFG__S2_OL_SRC_EN ; 
 int HII2S_IF_CLK_EN_CFG__ST_DL_L_EN ; 
 int HII2S_IF_CLK_EN_CFG__ST_DL_R_EN ; 
 int /*<<< orphan*/  HII2S_MUX_TOP_MODULE_CFG ; 
 int HII2S_MUX_TOP_MODULE_CFG__S2_OL_MIXER_IN1_MUTE ; 
 int HII2S_MUX_TOP_MODULE_CFG__S2_OL_MIXER_IN2_MUTE ; 
 int HII2S_MUX_TOP_MODULE_CFG__VOICE_DLINK_MIXER_IN1_MUTE ; 
 int HII2S_MUX_TOP_MODULE_CFG__VOICE_DLINK_MIXER_IN2_MUTE ; 
 scalar_t__ HII2S_STEREO_UPLINK_CHANNEL ; 
 scalar_t__ HII2S_ST_DL_CHANNEL ; 
 int /*<<< orphan*/  HII2S_ST_DL_FIFO_TH_CFG ; 
 int HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AEMPTY_MASK ; 
 int HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AEMPTY_SHIFT ; 
 int HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AFULL_MASK ; 
 int HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AFULL_SHIFT ; 
 int HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AEMPTY_MASK ; 
 int HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AEMPTY_SHIFT ; 
 int HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AFULL_MASK ; 
 int HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AFULL_SHIFT ; 
#define  SNDRV_PCM_FORMAT_S16_LE 136 
#define  SNDRV_PCM_FORMAT_S24_LE 135 
#define  SNDRV_PCM_FORMAT_U16_LE 134 
#define  SNDRV_PCM_FORMAT_U24_LE 133 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SND_SOC_DAIFMT_CBM_CFM 132 
#define  SND_SOC_DAIFMT_CBS_CFS 131 
 int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
 int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct hi6210_i2s* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int hi6210_read_reg (struct hi6210_i2s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi6210_write_reg (struct hi6210_i2s*,int /*<<< orphan*/ ,int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 struct snd_dmaengine_dai_dma_data* snd_soc_dai_get_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*) ; 

__attribute__((used)) static int hi6210_i2s_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *cpu_dai)
{
	struct hi6210_i2s *i2s = dev_get_drvdata(cpu_dai->dev);
	u32 bits = 0, rate = 0, signed_data = 0, fmt = 0;
	u32 val;
	struct snd_dmaengine_dai_dma_data *dma_data;

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_U16_LE:
		signed_data = HII2S_I2S_CFG__S2_CODEC_DATA_FORMAT;
		/* fall through */
	case SNDRV_PCM_FORMAT_S16_LE:
		bits = HII2S_BITS_16;
		break;
	case SNDRV_PCM_FORMAT_U24_LE:
		signed_data = HII2S_I2S_CFG__S2_CODEC_DATA_FORMAT;
		/* fall through */
	case SNDRV_PCM_FORMAT_S24_LE:
		bits = HII2S_BITS_24;
		break;
	default:
		dev_err(cpu_dai->dev, "Bad format\n");
		return -EINVAL;
	}


	switch (params_rate(params)) {
	case 8000:
		rate = HII2S_FS_RATE_8KHZ;
		break;
	case 16000:
		rate = HII2S_FS_RATE_16KHZ;
		break;
	case 32000:
		rate = HII2S_FS_RATE_32KHZ;
		break;
	case 48000:
		rate = HII2S_FS_RATE_48KHZ;
		break;
	case 96000:
		rate = HII2S_FS_RATE_96KHZ;
		break;
	case 192000:
		rate = HII2S_FS_RATE_192KHZ;
		break;
	default:
		dev_err(cpu_dai->dev, "Bad rate: %d\n", params_rate(params));
		return -EINVAL;
	}

	if (!(params_channels(params))) {
		dev_err(cpu_dai->dev, "Bad channels\n");
		return -EINVAL;
	}

	dma_data = snd_soc_dai_get_dma_data(cpu_dai, substream);

	switch (bits) {
	case HII2S_BITS_24:
		i2s->bits = 32;
		dma_data->addr_width = 3;
		break;
	default:
		i2s->bits = 16;
		dma_data->addr_width = 2;
		break;
	}
	i2s->rate = params_rate(params);
	i2s->channels = params_channels(params);
	i2s->channel_length = i2s->channels * i2s->bits;

	val = hi6210_read_reg(i2s, HII2S_ST_DL_FIFO_TH_CFG);
	val &= ~((HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AEMPTY_MASK <<
			HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AEMPTY_SHIFT) |
		(HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AFULL_MASK <<
			HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AFULL_SHIFT) |
		(HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AEMPTY_MASK <<
			HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AEMPTY_SHIFT) |
		(HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AFULL_MASK <<
			HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AFULL_SHIFT));
	val |= ((16 << HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AEMPTY_SHIFT) |
		(30 << HII2S_ST_DL_FIFO_TH_CFG__ST_DL_R_AFULL_SHIFT) |
		(16 << HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AEMPTY_SHIFT) |
		(30 << HII2S_ST_DL_FIFO_TH_CFG__ST_DL_L_AFULL_SHIFT));
	hi6210_write_reg(i2s, HII2S_ST_DL_FIFO_TH_CFG, val);


	val = hi6210_read_reg(i2s, HII2S_IF_CLK_EN_CFG);
	val |= (BIT(19) | BIT(18) | BIT(17) |
		HII2S_IF_CLK_EN_CFG__S2_IF_CLK_EN |
		HII2S_IF_CLK_EN_CFG__S2_OL_MIXER_EN |
		HII2S_IF_CLK_EN_CFG__S2_OL_SRC_EN |
		HII2S_IF_CLK_EN_CFG__ST_DL_R_EN |
		HII2S_IF_CLK_EN_CFG__ST_DL_L_EN);
	hi6210_write_reg(i2s, HII2S_IF_CLK_EN_CFG, val);


	val = hi6210_read_reg(i2s, HII2S_DIG_FILTER_CLK_EN_CFG);
	val &= ~(HII2S_DIG_FILTER_CLK_EN_CFG__DACR_SDM_EN |
		 HII2S_DIG_FILTER_CLK_EN_CFG__DACR_HBF2I_EN |
		 HII2S_DIG_FILTER_CLK_EN_CFG__DACR_AGC_EN |
		 HII2S_DIG_FILTER_CLK_EN_CFG__DACL_SDM_EN |
		 HII2S_DIG_FILTER_CLK_EN_CFG__DACL_HBF2I_EN |
		 HII2S_DIG_FILTER_CLK_EN_CFG__DACL_AGC_EN);
	val |= (HII2S_DIG_FILTER_CLK_EN_CFG__DACR_MIXER_EN |
		HII2S_DIG_FILTER_CLK_EN_CFG__DACL_MIXER_EN);
	hi6210_write_reg(i2s, HII2S_DIG_FILTER_CLK_EN_CFG, val);


	val = hi6210_read_reg(i2s, HII2S_DIG_FILTER_MODULE_CFG);
	val &= ~(HII2S_DIG_FILTER_MODULE_CFG__DACR_MIXER_IN2_MUTE |
		 HII2S_DIG_FILTER_MODULE_CFG__DACL_MIXER_IN2_MUTE);
	hi6210_write_reg(i2s, HII2S_DIG_FILTER_MODULE_CFG, val);

	val = hi6210_read_reg(i2s, HII2S_MUX_TOP_MODULE_CFG);
	val &= ~(HII2S_MUX_TOP_MODULE_CFG__S2_OL_MIXER_IN1_MUTE |
		 HII2S_MUX_TOP_MODULE_CFG__S2_OL_MIXER_IN2_MUTE |
		 HII2S_MUX_TOP_MODULE_CFG__VOICE_DLINK_MIXER_IN1_MUTE |
		 HII2S_MUX_TOP_MODULE_CFG__VOICE_DLINK_MIXER_IN2_MUTE);
	hi6210_write_reg(i2s, HII2S_MUX_TOP_MODULE_CFG, val);


	switch (i2s->format & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		i2s->master = false;
		val = hi6210_read_reg(i2s, HII2S_I2S_CFG);
		val |= HII2S_I2S_CFG__S2_MST_SLV;
		hi6210_write_reg(i2s, HII2S_I2S_CFG, val);
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		i2s->master = true;
		val = hi6210_read_reg(i2s, HII2S_I2S_CFG);
		val &= ~HII2S_I2S_CFG__S2_MST_SLV;
		hi6210_write_reg(i2s, HII2S_I2S_CFG, val);
		break;
	default:
		WARN_ONCE(1, "Invalid i2s->fmt MASTER_MASK. This shouldn't happen\n");
		return -EINVAL;
	}

	switch (i2s->format & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		fmt = HII2S_FORMAT_I2S;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		fmt = HII2S_FORMAT_LEFT_JUST;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		fmt = HII2S_FORMAT_RIGHT_JUST;
		break;
	default:
		WARN_ONCE(1, "Invalid i2s->fmt FORMAT_MASK. This shouldn't happen\n");
		return -EINVAL;
	}

	val = hi6210_read_reg(i2s, HII2S_I2S_CFG);
	val &= ~(HII2S_I2S_CFG__S2_FUNC_MODE_MASK <<
			HII2S_I2S_CFG__S2_FUNC_MODE_SHIFT);
	val |= fmt << HII2S_I2S_CFG__S2_FUNC_MODE_SHIFT;
	hi6210_write_reg(i2s, HII2S_I2S_CFG, val);


	val = hi6210_read_reg(i2s, HII2S_CLK_SEL);
	val &= ~(HII2S_CLK_SEL__I2S_BT_FM_SEL | /* BT gets the I2S */
			HII2S_CLK_SEL__EXT_12_288MHZ_SEL);
	hi6210_write_reg(i2s, HII2S_CLK_SEL, val);

	dma_data->maxburst = 2;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dma_data->addr = i2s->base_phys + HII2S_ST_DL_CHANNEL;
	else
		dma_data->addr = i2s->base_phys + HII2S_STEREO_UPLINK_CHANNEL;

	switch (i2s->channels) {
	case 1:
		val = hi6210_read_reg(i2s, HII2S_I2S_CFG);
		val |= HII2S_I2S_CFG__S2_FRAME_MODE;
		hi6210_write_reg(i2s, HII2S_I2S_CFG, val);
		break;
	default:
		val = hi6210_read_reg(i2s, HII2S_I2S_CFG);
		val &= ~HII2S_I2S_CFG__S2_FRAME_MODE;
		hi6210_write_reg(i2s, HII2S_I2S_CFG, val);
		break;
	}

	/* clear loopback, set signed type and word length */
	val = hi6210_read_reg(i2s, HII2S_I2S_CFG);
	val &= ~HII2S_I2S_CFG__S2_CODEC_DATA_FORMAT;
	val &= ~(HII2S_I2S_CFG__S2_CODEC_IO_WORDLENGTH_MASK <<
			HII2S_I2S_CFG__S2_CODEC_IO_WORDLENGTH_SHIFT);
	val &= ~(HII2S_I2S_CFG__S2_DIRECT_LOOP_MASK <<
			HII2S_I2S_CFG__S2_DIRECT_LOOP_SHIFT);
	val |= signed_data;
	val |= (bits << HII2S_I2S_CFG__S2_CODEC_IO_WORDLENGTH_SHIFT);
	hi6210_write_reg(i2s, HII2S_I2S_CFG, val);


	if (!i2s->master)
		return 0;

	/* set DAC and related units to correct rate */
	val = hi6210_read_reg(i2s, HII2S_FS_CFG);
	val &= ~(HII2S_FS_CFG__FS_S2_MASK << HII2S_FS_CFG__FS_S2_SHIFT);
	val &= ~(HII2S_FS_CFG__FS_DACLR_MASK << HII2S_FS_CFG__FS_DACLR_SHIFT);
	val &= ~(HII2S_FS_CFG__FS_ST_DL_R_MASK <<
					HII2S_FS_CFG__FS_ST_DL_R_SHIFT);
	val &= ~(HII2S_FS_CFG__FS_ST_DL_L_MASK <<
					HII2S_FS_CFG__FS_ST_DL_L_SHIFT);
	val |= (rate << HII2S_FS_CFG__FS_S2_SHIFT);
	val |= (rate << HII2S_FS_CFG__FS_DACLR_SHIFT);
	val |= (rate << HII2S_FS_CFG__FS_ST_DL_R_SHIFT);
	val |= (rate << HII2S_FS_CFG__FS_ST_DL_L_SHIFT);
	hi6210_write_reg(i2s, HII2S_FS_CFG, val);

	return 0;
}