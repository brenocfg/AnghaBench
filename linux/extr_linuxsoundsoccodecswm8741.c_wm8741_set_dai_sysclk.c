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
struct wm8741_priv {unsigned int sysclk; int /*<<< orphan*/ * sysclk_constraints; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  constraints_11289 ; 
 int /*<<< orphan*/  constraints_12288 ; 
 int /*<<< orphan*/  constraints_16384 ; 
 int /*<<< orphan*/  constraints_16934 ; 
 int /*<<< orphan*/  constraints_18432 ; 
 int /*<<< orphan*/  constraints_22579 ; 
 int /*<<< orphan*/  constraints_24576 ; 
 int /*<<< orphan*/  constraints_36864 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct wm8741_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8741_set_dai_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct wm8741_priv *wm8741 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "wm8741_set_dai_sysclk info: freq=%dHz\n", freq);

	switch (freq) {
	case 0:
		wm8741->sysclk_constraints = NULL;
		break;
	case 11289600:
		wm8741->sysclk_constraints = &constraints_11289;
		break;
	case 12288000:
		wm8741->sysclk_constraints = &constraints_12288;
		break;
	case 16384000:
		wm8741->sysclk_constraints = &constraints_16384;
		break;
	case 16934400:
		wm8741->sysclk_constraints = &constraints_16934;
		break;
	case 18432000:
		wm8741->sysclk_constraints = &constraints_18432;
		break;
	case 22579200:
	case 33868800:
		wm8741->sysclk_constraints = &constraints_22579;
		break;
	case 24576000:
		wm8741->sysclk_constraints = &constraints_24576;
		break;
	case 36864000:
		wm8741->sysclk_constraints = &constraints_36864;
		break;
	default:
		return -EINVAL;
	}

	wm8741->sysclk = freq;
	return 0;
}