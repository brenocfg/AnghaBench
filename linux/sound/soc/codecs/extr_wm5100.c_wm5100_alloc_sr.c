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
struct wm5100_priv {int sysclk; int /*<<< orphan*/  asyncclk; int /*<<< orphan*/ * sr_ref; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int WM5100_SAMPLE_RATE_1_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct wm5100_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 
 int* wm5100_sr_code ; 
 int* wm5100_sr_regs ; 

__attribute__((used)) static int wm5100_alloc_sr(struct snd_soc_component *component, int rate)
{
	struct wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);
	int sr_code, sr_free, i;

	for (i = 0; i < ARRAY_SIZE(wm5100_sr_code); i++)
		if (wm5100_sr_code[i] == rate)
			break;
	if (i == ARRAY_SIZE(wm5100_sr_code)) {
		dev_err(component->dev, "Unsupported sample rate: %dHz\n", rate);
		return -EINVAL;
	}
	sr_code = i;

	if ((wm5100->sysclk % rate) == 0) {
		/* Is this rate already in use? */
		sr_free = -1;
		for (i = 0; i < ARRAY_SIZE(wm5100_sr_regs); i++) {
			if (!wm5100->sr_ref[i] && sr_free == -1) {
				sr_free = i;
				continue;
			}
			if ((snd_soc_component_read32(component, wm5100_sr_regs[i]) &
			     WM5100_SAMPLE_RATE_1_MASK) == sr_code)
				break;
		}

		if (i < ARRAY_SIZE(wm5100_sr_regs)) {
			wm5100->sr_ref[i]++;
			dev_dbg(component->dev, "SR %dHz, slot %d, ref %d\n",
				rate, i, wm5100->sr_ref[i]);
			return i;
		}

		if (sr_free == -1) {
			dev_err(component->dev, "All SR slots already in use\n");
			return -EBUSY;
		}

		dev_dbg(component->dev, "Allocating SR slot %d for %dHz\n",
			sr_free, rate);
		wm5100->sr_ref[sr_free]++;
		snd_soc_component_update_bits(component, wm5100_sr_regs[sr_free],
				    WM5100_SAMPLE_RATE_1_MASK,
				    sr_code);

		return sr_free;

	} else {
		dev_err(component->dev,
			"SR %dHz incompatible with %dHz SYSCLK and %dHz ASYNCCLK\n",
			rate, wm5100->sysclk, wm5100->asyncclk);
		return -EINVAL;
	}
}