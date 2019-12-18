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
struct snd_pcm_hw_params {int dummy; } ;
struct oxygen {int dummy; } ;

/* Variables and functions */
 int WM8776_ADCOSR ; 
 int WM8776_ADCRATE_256 ; 
 int WM8776_DACRATE_256 ; 
 int /*<<< orphan*/  WM8776_MSTRCTRL ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  wm8776_write_cached (struct oxygen*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_wm8776_adc_params(struct oxygen *chip,
				  struct snd_pcm_hw_params *params)
{
	u16 reg;

	reg = WM8776_ADCRATE_256 | WM8776_DACRATE_256;
	if (params_rate(params) > 48000)
		reg |= WM8776_ADCOSR;
	wm8776_write_cached(chip, WM8776_MSTRCTRL, reg);
}