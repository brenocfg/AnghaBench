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
struct xonar_wm87x6 {int* wm8766_regs; } ;
struct oxygen {int* dac_volume; scalar_t__ dac_mute; struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 size_t WM8766_DAC_CTRL ; 
 size_t WM8766_DAC_CTRL2 ; 
 int WM8766_DMUTE_MASK ; 
 int WM8766_FMT_LJUST ; 
 size_t WM8766_INT_CTRL ; 
 int WM8766_IWL_24 ; 
 size_t WM8766_LDA1 ; 
 size_t WM8766_LDA2 ; 
 size_t WM8766_LDA3 ; 
 size_t WM8766_RDA1 ; 
 size_t WM8766_RDA2 ; 
 size_t WM8766_RDA3 ; 
 size_t WM8766_RESET ; 
 int WM8766_UPDATE ; 
 int WM8766_ZCD ; 
 int /*<<< orphan*/  wm8766_write (struct oxygen*,size_t,int) ; 

__attribute__((used)) static void wm8766_registers_init(struct oxygen *chip)
{
	struct xonar_wm87x6 *data = chip->model_data;

	wm8766_write(chip, WM8766_RESET, 0);
	wm8766_write(chip, WM8766_DAC_CTRL, data->wm8766_regs[WM8766_DAC_CTRL]);
	wm8766_write(chip, WM8766_INT_CTRL, WM8766_FMT_LJUST | WM8766_IWL_24);
	wm8766_write(chip, WM8766_DAC_CTRL2,
		     WM8766_ZCD | (chip->dac_mute ? WM8766_DMUTE_MASK : 0));
	wm8766_write(chip, WM8766_LDA1, chip->dac_volume[2]);
	wm8766_write(chip, WM8766_RDA1, chip->dac_volume[3]);
	wm8766_write(chip, WM8766_LDA2, chip->dac_volume[4]);
	wm8766_write(chip, WM8766_RDA2, chip->dac_volume[5]);
	wm8766_write(chip, WM8766_LDA3, chip->dac_volume[6]);
	wm8766_write(chip, WM8766_RDA3, chip->dac_volume[7] | WM8766_UPDATE);
}