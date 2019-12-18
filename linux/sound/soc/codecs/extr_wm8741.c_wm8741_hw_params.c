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
struct wm8741_priv {int /*<<< orphan*/  sysclk; TYPE_1__* sysclk_constraints; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {int count; int* list; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WM8741_FORMAT_CONTROL ; 
 int /*<<< orphan*/  WM8741_IWL_MASK ; 
 int /*<<< orphan*/  WM8741_MODE_CONTROL_1 ; 
 int /*<<< orphan*/  WM8741_OSR_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct wm8741_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int wm8741_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wm8741_priv *wm8741 = snd_soc_component_get_drvdata(component);
	unsigned int iface, mode;
	int i;

	/* The set of sample rates that can be supported depends on the
	 * MCLK supplied to the CODEC - enforce this.
	 */
	if (!wm8741->sysclk) {
		dev_err(component->dev,
			"No MCLK configured, call set_sysclk() on init or in hw_params\n");
		return -EINVAL;
	}

	/* Find a supported LRCLK rate */
	for (i = 0; i < wm8741->sysclk_constraints->count; i++) {
		if (wm8741->sysclk_constraints->list[i] == params_rate(params))
			break;
	}

	if (i == wm8741->sysclk_constraints->count) {
		dev_err(component->dev, "LRCLK %d unsupported with MCLK %d\n",
			params_rate(params), wm8741->sysclk);
		return -EINVAL;
	}

	/* bit size */
	switch (params_width(params)) {
	case 16:
		iface = 0x0;
		break;
	case 20:
		iface = 0x1;
		break;
	case 24:
		iface = 0x2;
		break;
	case 32:
		iface = 0x3;
		break;
	default:
		dev_dbg(component->dev, "wm8741_hw_params:    Unsupported bit size param = %d",
			params_width(params));
		return -EINVAL;
	}

	/* oversampling rate */
	if (params_rate(params) > 96000)
		mode = 0x40;
	else if (params_rate(params) > 48000)
		mode = 0x20;
	else
		mode = 0x00;

	dev_dbg(component->dev, "wm8741_hw_params:    bit size param = %d, rate param = %d",
		params_width(params), params_rate(params));

	snd_soc_component_update_bits(component, WM8741_FORMAT_CONTROL, WM8741_IWL_MASK,
			    iface);
	snd_soc_component_update_bits(component, WM8741_MODE_CONTROL_1, WM8741_OSR_MASK,
			    mode);

	return 0;
}