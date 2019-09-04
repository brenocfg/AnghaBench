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
typedef  int u16 ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8753_CLOCK ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int wm8753_vdac_adc_set_dai_fmt (struct snd_soc_component*,unsigned int) ; 

__attribute__((used)) static int wm8753_mode1v_set_dai_fmt(struct snd_soc_component *component,
		unsigned int fmt)
{
	u16 clock;

	/* set clk source as pcmclk */
	clock = snd_soc_component_read32(component, WM8753_CLOCK) & 0xfffb;
	snd_soc_component_write(component, WM8753_CLOCK, clock);

	return wm8753_vdac_adc_set_dai_fmt(component, fmt);
}