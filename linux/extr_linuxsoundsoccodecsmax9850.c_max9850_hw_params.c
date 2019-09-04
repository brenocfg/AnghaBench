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
typedef  int u8 ;
typedef  int u64 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct max9850_priv {int /*<<< orphan*/  sysclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX9850_CLOCK ; 
 int /*<<< orphan*/  MAX9850_DIGITAL_AUDIO ; 
 int /*<<< orphan*/  MAX9850_LRCLK_LSB ; 
 int /*<<< orphan*/  MAX9850_LRCLK_MSB ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct max9850_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max9850_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct max9850_priv *max9850 = snd_soc_component_get_drvdata(component);
	u64 lrclk_div;
	u8 sf, da;

	if (!max9850->sysclk)
		return -EINVAL;

	/* lrclk_div = 2^22 * rate / iclk with iclk = mclk / sf */
	sf = (snd_soc_component_read32(component, MAX9850_CLOCK) >> 2) + 1;
	lrclk_div = (1 << 22);
	lrclk_div *= params_rate(params);
	lrclk_div *= sf;
	do_div(lrclk_div, max9850->sysclk);

	snd_soc_component_write(component, MAX9850_LRCLK_MSB, (lrclk_div >> 8) & 0x7f);
	snd_soc_component_write(component, MAX9850_LRCLK_LSB, lrclk_div & 0xff);

	switch (params_width(params)) {
	case 16:
		da = 0;
		break;
	case 20:
		da = 0x2;
		break;
	case 24:
		da = 0x3;
		break;
	default:
		return -EINVAL;
	}
	snd_soc_component_update_bits(component, MAX9850_DIGITAL_AUDIO, 0x3, da);

	return 0;
}