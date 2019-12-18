#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ count; } ;
struct wm8524_priv {unsigned int sysclk; unsigned int* rate_constraint_list; TYPE_1__ rate_constraint; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {unsigned int ratio; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 TYPE_2__* lrclk_ratios ; 
 struct wm8524_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8524_set_dai_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct wm8524_priv *wm8524 = snd_soc_component_get_drvdata(component);
	unsigned int val;
	int i, j = 0;

	wm8524->sysclk = freq;

	wm8524->rate_constraint.count = 0;
	for (i = 0; i < ARRAY_SIZE(lrclk_ratios); i++) {
		val = freq / lrclk_ratios[i].ratio;
		/* Check that it's a standard rate since core can't
		 * cope with others and having the odd rates confuses
		 * constraint matching.
		 */
		switch (val) {
		case 8000:
		case 32000:
		case 44100:
		case 48000:
		case 88200:
		case 96000:
		case 176400:
		case 192000:
			dev_dbg(component->dev, "Supported sample rate: %dHz\n",
				val);
			wm8524->rate_constraint_list[j++] = val;
			wm8524->rate_constraint.count++;
			break;
		default:
			dev_dbg(component->dev, "Skipping sample rate: %dHz\n",
				val);
		}
	}

	/* Need at least one supported rate... */
	if (wm8524->rate_constraint.count == 0)
		return -EINVAL;

	return 0;
}