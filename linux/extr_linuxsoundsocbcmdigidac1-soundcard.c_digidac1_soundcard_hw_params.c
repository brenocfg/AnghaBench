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
struct snd_soc_pcm_runtime {struct snd_soc_dai* codec_dai; struct snd_soc_card* card; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; TYPE_1__* dai_link; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_OUT ; 
 int /*<<< orphan*/  WM8741_FORMAT_CONTROL ; 
 int WM8741_IWL_MASK ; 
 int /*<<< orphan*/  WM8741_MODE_CONTROL_1 ; 
 int WM8741_OSR_MASK ; 
 int WM8804_MCLKDIV_128FS ; 
 int WM8804_MCLKDIV_256FS ; 
 int /*<<< orphan*/  WM8804_MCLK_DIV ; 
 int /*<<< orphan*/  WM8804_PWRDN ; 
 int /*<<< orphan*/  WM8804_SPDTX4 ; 
 int /*<<< orphan*/  WM8804_TX_CLKSRC_PLL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int samplerate ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int snd_soc_dai_set_bclk_ratio (struct snd_soc_dai*,int) ; 
 int /*<<< orphan*/  snd_soc_dai_set_clkdiv (struct snd_soc_dai*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_dai_set_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,long) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct snd_soc_pcm_runtime* snd_soc_get_pcm_runtime (struct snd_soc_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int digidac1_soundcard_hw_params(struct snd_pcm_substream *substream,
				       struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_component *component = rtd->codec_dai->component;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct snd_soc_card *card = rtd->card;
	struct snd_soc_pcm_runtime *wm8741_rtd;
	struct snd_soc_component *wm8741_component;

	int sysclk = 27000000;
	long mclk_freq = 0;
	int mclk_div = 1;
	int sampling_freq = 1;
	int ret;

	wm8741_rtd = snd_soc_get_pcm_runtime(card, card->dai_link[1].name);
	if (!wm8741_rtd) {
		dev_warn(card->dev, "digidac1_soundcard_hw_params: couldn't get WM8741 rtd\n");
		return -EFAULT;
	}
	wm8741_component = wm8741_rtd->codec_dai->component;
	samplerate = params_rate(params);

	if (samplerate <= 96000) {
		mclk_freq = samplerate*256;
		mclk_div = WM8804_MCLKDIV_256FS;
	} else {
		mclk_freq = samplerate*128;
		mclk_div = WM8804_MCLKDIV_128FS;
		}

	switch (samplerate) {
	case 32000:
		sampling_freq = 0x03;
		break;
	case 44100:
		sampling_freq = 0x00;
		break;
	case 48000:
		sampling_freq = 0x02;
		break;
	case 88200:
		sampling_freq = 0x08;
		break;
	case 96000:
		sampling_freq = 0x0a;
		break;
	case 176400:
		sampling_freq = 0x0c;
		break;
	case 192000:
		sampling_freq = 0x0e;
		break;
	default:
		dev_err(card->dev,
		"Failed to set WM8804 SYSCLK, unsupported samplerate %d\n",
		samplerate);
	}

	snd_soc_dai_set_clkdiv(codec_dai, WM8804_MCLK_DIV, mclk_div);
	snd_soc_dai_set_pll(codec_dai, 0, 0, sysclk, mclk_freq);

	ret = snd_soc_dai_set_sysclk(codec_dai, WM8804_TX_CLKSRC_PLL,
		sysclk, SND_SOC_CLOCK_OUT);
	if (ret < 0) {
		dev_err(card->dev,
		"Failed to set WM8804 SYSCLK: %d\n", ret);
		return ret;
	}
	/* Enable wm8804 TX output */
	snd_soc_component_update_bits(component, WM8804_PWRDN, 0x4, 0x0);

	/* wm8804 Power on */
	snd_soc_component_update_bits(component, WM8804_PWRDN, 0x9, 0);

	/* wm8804 set sampling frequency status bits */
	snd_soc_component_update_bits(component, WM8804_SPDTX4, 0x0f, sampling_freq);

	/* Now update wm8741 registers for the correct oversampling */
	if (samplerate <= 48000)
		snd_soc_component_update_bits(wm8741_component, WM8741_MODE_CONTROL_1,
		 WM8741_OSR_MASK, 0x00);
	else if (samplerate <= 96000)
		snd_soc_component_update_bits(wm8741_component, WM8741_MODE_CONTROL_1,
		 WM8741_OSR_MASK, 0x20);
	else
		snd_soc_component_update_bits(wm8741_component, WM8741_MODE_CONTROL_1,
		 WM8741_OSR_MASK, 0x40);

	/* wm8741 bit size */
	switch (params_width(params)) {
	case 16:
		snd_soc_component_update_bits(wm8741_component, WM8741_FORMAT_CONTROL,
		 WM8741_IWL_MASK, 0x00);
		break;
	case 20:
		snd_soc_component_update_bits(wm8741_component, WM8741_FORMAT_CONTROL,
		 WM8741_IWL_MASK, 0x01);
		break;
	case 24:
		snd_soc_component_update_bits(wm8741_component, WM8741_FORMAT_CONTROL,
		 WM8741_IWL_MASK, 0x02);
		break;
	case 32:
		snd_soc_component_update_bits(wm8741_component, WM8741_FORMAT_CONTROL,
		 WM8741_IWL_MASK, 0x03);
		break;
	default:
		dev_dbg(card->dev, "wm8741_hw_params:    Unsupported bit size param = %d",
			params_width(params));
		return -EINVAL;
	}

	return snd_soc_dai_set_bclk_ratio(cpu_dai, 64);
}