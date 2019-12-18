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
struct wm9712_priv {int /*<<< orphan*/  ac97; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  WM9712_VENDOR_ID ; 
 int /*<<< orphan*/  WM9712_VENDOR_ID_MASK ; 
 int snd_ac97_reset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_cache_sync (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_force_bias_level (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct wm9712_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int wm9712_soc_resume(struct snd_soc_component *component)
{
	struct wm9712_priv *wm9712 = snd_soc_component_get_drvdata(component);
	int ret;

	ret = snd_ac97_reset(wm9712->ac97, true, WM9712_VENDOR_ID,
		WM9712_VENDOR_ID_MASK);
	if (ret < 0)
		return ret;

	snd_soc_component_force_bias_level(component, SND_SOC_BIAS_STANDBY);

	if (ret == 0)
		snd_soc_component_cache_sync(component);

	return ret;
}