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
struct xonar_wm87x6 {int* wm8776_regs; } ;
struct oxygen {int* dac_volume; scalar_t__ dac_mute; struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 size_t WM8776_ADCIFCTRL ; 
 size_t WM8776_ADCLVOL ; 
 size_t WM8776_ADCMUX ; 
 size_t WM8776_ADCRVOL ; 
 size_t WM8776_DACCTRL1 ; 
 int WM8776_DACFMT_LJUST ; 
 size_t WM8776_DACIFCTRL ; 
 size_t WM8776_DACLVOL ; 
 size_t WM8776_DACMUTE ; 
 size_t WM8776_DACRVOL ; 
 int WM8776_DACWL_24 ; 
 int WM8776_DMUTE ; 
 int WM8776_DZCEN ; 
 size_t WM8776_HPLVOL ; 
 size_t WM8776_HPRVOL ; 
 size_t WM8776_MSTRCTRL ; 
 size_t WM8776_PHASESWAP ; 
 int WM8776_PH_MASK ; 
 int WM8776_PL_LEFT_LEFT ; 
 int WM8776_PL_RIGHT_RIGHT ; 
 size_t WM8776_PWRDOWN ; 
 size_t WM8776_RESET ; 
 int WM8776_UPDATE ; 
 int /*<<< orphan*/  wm8776_write (struct oxygen*,size_t,int) ; 

__attribute__((used)) static void wm8776_registers_init(struct oxygen *chip)
{
	struct xonar_wm87x6 *data = chip->model_data;

	wm8776_write(chip, WM8776_RESET, 0);
	wm8776_write(chip, WM8776_PHASESWAP, WM8776_PH_MASK);
	wm8776_write(chip, WM8776_DACCTRL1, WM8776_DZCEN |
		     WM8776_PL_LEFT_LEFT | WM8776_PL_RIGHT_RIGHT);
	wm8776_write(chip, WM8776_DACMUTE, chip->dac_mute ? WM8776_DMUTE : 0);
	wm8776_write(chip, WM8776_DACIFCTRL,
		     WM8776_DACFMT_LJUST | WM8776_DACWL_24);
	wm8776_write(chip, WM8776_ADCIFCTRL,
		     data->wm8776_regs[WM8776_ADCIFCTRL]);
	wm8776_write(chip, WM8776_MSTRCTRL, data->wm8776_regs[WM8776_MSTRCTRL]);
	wm8776_write(chip, WM8776_PWRDOWN, data->wm8776_regs[WM8776_PWRDOWN]);
	wm8776_write(chip, WM8776_HPLVOL, data->wm8776_regs[WM8776_HPLVOL]);
	wm8776_write(chip, WM8776_HPRVOL, data->wm8776_regs[WM8776_HPRVOL] |
		     WM8776_UPDATE);
	wm8776_write(chip, WM8776_ADCLVOL, data->wm8776_regs[WM8776_ADCLVOL]);
	wm8776_write(chip, WM8776_ADCRVOL, data->wm8776_regs[WM8776_ADCRVOL]);
	wm8776_write(chip, WM8776_ADCMUX, data->wm8776_regs[WM8776_ADCMUX]);
	wm8776_write(chip, WM8776_DACLVOL, chip->dac_volume[0]);
	wm8776_write(chip, WM8776_DACRVOL, chip->dac_volume[1] | WM8776_UPDATE);
}