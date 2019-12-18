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
struct wm8971_priv {int /*<<< orphan*/  charge_work; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM8971_LDAC ; 
 int /*<<< orphan*/  WM8971_LINVOL ; 
 int /*<<< orphan*/  WM8971_LOUT1V ; 
 int /*<<< orphan*/  WM8971_LOUT2V ; 
 int /*<<< orphan*/  WM8971_RDAC ; 
 int /*<<< orphan*/  WM8971_RINVOL ; 
 int /*<<< orphan*/  WM8971_ROUT1V ; 
 int /*<<< orphan*/  WM8971_ROUT2V ; 
 struct wm8971_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wm8971_charge_work ; 
 int /*<<< orphan*/  wm8971_reset (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8971_probe(struct snd_soc_component *component)
{
	struct wm8971_priv *wm8971 = snd_soc_component_get_drvdata(component);

	INIT_DELAYED_WORK(&wm8971->charge_work, wm8971_charge_work);

	wm8971_reset(component);

	/* set the update bits */
	snd_soc_component_update_bits(component, WM8971_LDAC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_RDAC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_LOUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_ROUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_LOUT2V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_ROUT2V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_LINVOL, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_RINVOL, 0x0100, 0x0100);

	return 0;
}