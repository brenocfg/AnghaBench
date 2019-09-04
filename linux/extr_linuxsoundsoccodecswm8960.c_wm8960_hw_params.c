#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct wm8960_priv {int bclk; int* is_stream_in_use; scalar_t__ lrclk; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_3__ {scalar_t__ rate; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ SND_SOC_BIAS_ON ; 
 int /*<<< orphan*/  WM8960_ADDCTL3 ; 
 int /*<<< orphan*/  WM8960_IFACE1 ; 
 TYPE_1__* alc_rates ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 scalar_t__ params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 scalar_t__ snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8960_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int snd_soc_params_to_bclk (struct snd_pcm_hw_params*) ; 
 int wm8960_configure_clocking (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8960_set_deemph (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8960_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	u16 iface = snd_soc_component_read32(component, WM8960_IFACE1) & 0xfff3;
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	int i;

	wm8960->bclk = snd_soc_params_to_bclk(params);
	if (params_channels(params) == 1)
		wm8960->bclk *= 2;

	/* bit size */
	switch (params_width(params)) {
	case 16:
		break;
	case 20:
		iface |= 0x0004;
		break;
	case 24:
		iface |= 0x0008;
		break;
	case 32:
		/* right justify mode does not support 32 word length */
		if ((iface & 0x3) != 0) {
			iface |= 0x000c;
			break;
		}
		/* fall through */
	default:
		dev_err(component->dev, "unsupported width %d\n",
			params_width(params));
		return -EINVAL;
	}

	wm8960->lrclk = params_rate(params);
	/* Update filters for the new rate */
	if (tx) {
		wm8960_set_deemph(component);
	} else {
		for (i = 0; i < ARRAY_SIZE(alc_rates); i++)
			if (alc_rates[i].rate == params_rate(params))
				snd_soc_component_update_bits(component,
						    WM8960_ADDCTL3, 0x7,
						    alc_rates[i].val);
	}

	/* set iface */
	snd_soc_component_write(component, WM8960_IFACE1, iface);

	wm8960->is_stream_in_use[tx] = true;

	if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_ON &&
	    !wm8960->is_stream_in_use[!tx])
		return wm8960_configure_clocking(component);

	return 0;
}