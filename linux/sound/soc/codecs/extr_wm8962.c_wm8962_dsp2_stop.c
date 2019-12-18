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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8962_DSP2_EXECCONTROL ; 
 int /*<<< orphan*/  WM8962_DSP2_STOP ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8962_dsp2_set_enable (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8962_dsp2_stop(struct snd_soc_component *component)
{
	wm8962_dsp2_set_enable(component, 0);

	snd_soc_component_write(component, WM8962_DSP2_EXECCONTROL, WM8962_DSP2_STOP);

	return 0;
}