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
struct wm8978_priv {int /*<<< orphan*/  sysclk; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WM8978_PLL ; 
 struct wm8978_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * update_reg ; 

__attribute__((used)) static int wm8978_probe(struct snd_soc_component *component)
{
	struct wm8978_priv *wm8978 = snd_soc_component_get_drvdata(component);
	int i;

	/*
	 * Set default system clock to PLL, it is more precise, this is also the
	 * default hardware setting
	 */
	wm8978->sysclk = WM8978_PLL;

	/*
	 * Set the update bit in all registers, that have one. This way all
	 * writes to those registers will also cause the update bit to be
	 * written.
	 */
	for (i = 0; i < ARRAY_SIZE(update_reg); i++)
		snd_soc_component_update_bits(component, update_reg[i], 0x100, 0x100);

	return 0;
}