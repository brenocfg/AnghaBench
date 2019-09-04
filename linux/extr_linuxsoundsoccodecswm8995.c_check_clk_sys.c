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
struct snd_soc_dapm_widget {int /*<<< orphan*/  name; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8995_CLOCKING_1 ; 
 unsigned int WM8995_SYSCLK_SRC ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int check_clk_sys(struct snd_soc_dapm_widget *source,
			 struct snd_soc_dapm_widget *sink)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	unsigned int reg;
	const char *clk;

	reg = snd_soc_component_read32(component, WM8995_CLOCKING_1);
	/* Check what we're currently using for CLK_SYS */
	if (reg & WM8995_SYSCLK_SRC)
		clk = "AIF2CLK";
	else
		clk = "AIF1CLK";
	return !strcmp(source->name, clk);
}