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
struct oxygen {struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 int WM8776_ADCFMT_LJUST ; 
 size_t WM8776_ADCIFCTRL ; 
 size_t WM8776_ADCLVOL ; 
 int WM8776_ADCMCLK ; 
 size_t WM8776_ADCMUX ; 
 int WM8776_ADCRATE_256 ; 
 size_t WM8776_ADCRVOL ; 
 int WM8776_ADCWL_24 ; 
 int WM8776_DACRATE_256 ; 
 size_t WM8776_HPLVOL ; 
 int WM8776_HPPD ; 
 size_t WM8776_HPRVOL ; 
 int WM8776_HPZCEN ; 
 size_t WM8776_MSTRCTRL ; 
 size_t WM8776_PWRDOWN ; 
 int WM8776_ZCA ; 
 int /*<<< orphan*/  wm8776_registers_init (struct oxygen*) ; 

__attribute__((used)) static void wm8776_init(struct oxygen *chip)
{
	struct xonar_wm87x6 *data = chip->model_data;

	data->wm8776_regs[WM8776_HPLVOL] = (0x79 - 60) | WM8776_HPZCEN;
	data->wm8776_regs[WM8776_HPRVOL] = (0x79 - 60) | WM8776_HPZCEN;
	data->wm8776_regs[WM8776_ADCIFCTRL] =
		WM8776_ADCFMT_LJUST | WM8776_ADCWL_24 | WM8776_ADCMCLK;
	data->wm8776_regs[WM8776_MSTRCTRL] =
		WM8776_ADCRATE_256 | WM8776_DACRATE_256;
	data->wm8776_regs[WM8776_PWRDOWN] = WM8776_HPPD;
	data->wm8776_regs[WM8776_ADCLVOL] = 0xa5 | WM8776_ZCA;
	data->wm8776_regs[WM8776_ADCRVOL] = 0xa5 | WM8776_ZCA;
	data->wm8776_regs[WM8776_ADCMUX] = 0x001;
	wm8776_registers_init(chip);
}