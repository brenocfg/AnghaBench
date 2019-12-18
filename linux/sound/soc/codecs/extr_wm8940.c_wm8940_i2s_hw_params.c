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
typedef  int u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  WM8940_ADDCNTRL ; 
 int /*<<< orphan*/  WM8940_COMPANDINGCTL ; 
 int /*<<< orphan*/  WM8940_IFACE ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8940_i2s_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	u16 iface = snd_soc_component_read32(component, WM8940_IFACE) & 0xFD9F;
	u16 addcntrl = snd_soc_component_read32(component, WM8940_ADDCNTRL) & 0xFFF1;
	u16 companding =  snd_soc_component_read32(component,
						WM8940_COMPANDINGCTL) & 0xFFDF;
	int ret;

	/* LoutR control */
	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE
	    && params_channels(params) == 2)
		iface |= (1 << 9);

	switch (params_rate(params)) {
	case 8000:
		addcntrl |= (0x5 << 1);
		break;
	case 11025:
		addcntrl |= (0x4 << 1);
		break;
	case 16000:
		addcntrl |= (0x3 << 1);
		break;
	case 22050:
		addcntrl |= (0x2 << 1);
		break;
	case 32000:
		addcntrl |= (0x1 << 1);
		break;
	case 44100:
	case 48000:
		break;
	}
	ret = snd_soc_component_write(component, WM8940_ADDCNTRL, addcntrl);
	if (ret)
		goto error_ret;

	switch (params_width(params)) {
	case 8:
		companding = companding | (1 << 5);
		break;
	case 16:
		break;
	case 20:
		iface |= (1 << 5);
		break;
	case 24:
		iface |= (2 << 5);
		break;
	case 32:
		iface |= (3 << 5);
		break;
	}
	ret = snd_soc_component_write(component, WM8940_COMPANDINGCTL, companding);
	if (ret)
		goto error_ret;
	ret = snd_soc_component_write(component, WM8940_IFACE, iface);

error_ret:
	return ret;
}