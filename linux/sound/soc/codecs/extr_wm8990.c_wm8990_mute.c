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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8990_DAC_CTRL ; 
 int WM8990_DAC_MUTE ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8990_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_component *component = dai->component;
	u16 val;

	val  = snd_soc_component_read32(component, WM8990_DAC_CTRL) & ~WM8990_DAC_MUTE;

	if (mute)
		snd_soc_component_write(component, WM8990_DAC_CTRL, val | WM8990_DAC_MUTE);
	else
		snd_soc_component_write(component, WM8990_DAC_CTRL, val);

	return 0;
}