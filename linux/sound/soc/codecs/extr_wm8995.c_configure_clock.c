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
struct wm8995_priv {scalar_t__* aifclk; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8995_CLOCKING_1 ; 
 int WM8995_SYSCLK_SRC ; 
 int /*<<< orphan*/  WM8995_SYSCLK_SRC_MASK ; 
 int /*<<< orphan*/  configure_aif_clock (struct snd_soc_component*,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct wm8995_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static int configure_clock(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct wm8995_priv *wm8995;
	int change, new;

	wm8995 = snd_soc_component_get_drvdata(component);

	/* Bring up the AIF clocks first */
	configure_aif_clock(component, 0);
	configure_aif_clock(component, 1);

	/*
	 * Then switch CLK_SYS over to the higher of them; a change
	 * can only happen as a result of a clocking change which can
	 * only be made outside of DAPM so we can safely redo the
	 * clocking.
	 */

	/* If they're equal it doesn't matter which is used */
	if (wm8995->aifclk[0] == wm8995->aifclk[1])
		return 0;

	if (wm8995->aifclk[0] < wm8995->aifclk[1])
		new = WM8995_SYSCLK_SRC;
	else
		new = 0;

	change = snd_soc_component_update_bits(component, WM8995_CLOCKING_1,
				     WM8995_SYSCLK_SRC_MASK, new);
	if (!change)
		return 0;

	snd_soc_dapm_sync(dapm);

	return 0;
}