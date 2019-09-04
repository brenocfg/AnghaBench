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
struct xonar_wm87x6 {unsigned int* wm8766_regs; } ;
struct oxygen {struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 size_t WM8766_DAC_CTRL ; 
 unsigned int WM8766_PL_LEFT_LEFT ; 
 unsigned int WM8766_PL_LEFT_LRMIX ; 
 unsigned int WM8766_PL_LEFT_MASK ; 
 unsigned int WM8766_PL_RIGHT_LRMIX ; 
 unsigned int WM8766_PL_RIGHT_MASK ; 
 unsigned int WM8766_PL_RIGHT_RIGHT ; 
 int /*<<< orphan*/  wm8766_write_cached (struct oxygen*,size_t,unsigned int) ; 

__attribute__((used)) static void update_wm8766_center_lfe_mix(struct oxygen *chip, bool mixed)
{
	struct xonar_wm87x6 *data = chip->model_data;
	unsigned int reg;

	/*
	 * The WM8766 can mix left and right channels, but this setting
	 * applies to all three stereo pairs.
	 */
	reg = data->wm8766_regs[WM8766_DAC_CTRL] &
		~(WM8766_PL_LEFT_MASK | WM8766_PL_RIGHT_MASK);
	if (mixed)
		reg |= WM8766_PL_LEFT_LRMIX | WM8766_PL_RIGHT_LRMIX;
	else
		reg |= WM8766_PL_LEFT_LEFT | WM8766_PL_RIGHT_RIGHT;
	wm8766_write_cached(chip, WM8766_DAC_CTRL, reg);
}