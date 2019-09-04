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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8988_ADCTL2 ; 
 int /*<<< orphan*/  WM8988_PWR2 ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8988_lrc_control(struct snd_soc_dapm_widget *w,
			      struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 adctl2 = snd_soc_component_read32(component, WM8988_ADCTL2);

	/* Use the DAC to gate LRC if active, otherwise use ADC */
	if (snd_soc_component_read32(component, WM8988_PWR2) & 0x180)
		adctl2 &= ~0x4;
	else
		adctl2 |= 0x4;

	return snd_soc_component_write(component, WM8988_ADCTL2, adctl2);
}