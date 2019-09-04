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
struct wm8996_priv {int bg_ena; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8996_BG_ENA ; 
 int /*<<< orphan*/  WM8996_POWER_MANAGEMENT_1 ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct wm8996_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm8996_bg_enable(struct snd_soc_component *component)
{
	struct wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);

	wm8996->bg_ena++;
	if (wm8996->bg_ena == 1) {
		snd_soc_component_update_bits(component, WM8996_POWER_MANAGEMENT_1,
				    WM8996_BG_ENA, WM8996_BG_ENA);
		msleep(2);
	}
}