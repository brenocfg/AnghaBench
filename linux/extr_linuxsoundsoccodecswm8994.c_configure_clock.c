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
struct wm8994_priv {scalar_t__* aifclk; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8994_CLOCKING_1 ; 
 int WM8994_SYSCLK_SRC ; 
 int /*<<< orphan*/  configure_aif_clock (struct snd_soc_component*,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  wm8958_micd_set_rate (struct snd_soc_component*) ; 

__attribute__((used)) static int configure_clock(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	int change, new;

	/* Bring up the AIF clocks first */
	configure_aif_clock(component, 0);
	configure_aif_clock(component, 1);

	/* Then switch CLK_SYS over to the higher of them; a change
	 * can only happen as a result of a clocking change which can
	 * only be made outside of DAPM so we can safely redo the
	 * clocking.
	 */

	/* If they're equal it doesn't matter which is used */
	if (wm8994->aifclk[0] == wm8994->aifclk[1]) {
		wm8958_micd_set_rate(component);
		return 0;
	}

	if (wm8994->aifclk[0] < wm8994->aifclk[1])
		new = WM8994_SYSCLK_SRC;
	else
		new = 0;

	change = snd_soc_component_update_bits(component, WM8994_CLOCKING_1,
				     WM8994_SYSCLK_SRC, new);
	if (change)
		snd_soc_dapm_sync(dapm);

	wm8958_micd_set_rate(component);

	return 0;
}