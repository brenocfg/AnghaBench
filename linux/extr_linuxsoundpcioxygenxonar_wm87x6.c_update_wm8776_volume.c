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
typedef  int u8 ;
struct xonar_wm87x6 {int* wm8776_regs; } ;
struct oxygen {int* dac_volume; struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 size_t WM8776_DACLVOL ; 
 size_t WM8776_DACMASTER ; 
 size_t WM8776_DACRVOL ; 
 int WM8776_UPDATE ; 
 int /*<<< orphan*/  wm8776_write (struct oxygen*,size_t,int) ; 

__attribute__((used)) static void update_wm8776_volume(struct oxygen *chip)
{
	struct xonar_wm87x6 *data = chip->model_data;
	u8 to_change;

	if (chip->dac_volume[0] == chip->dac_volume[1]) {
		if (chip->dac_volume[0] != data->wm8776_regs[WM8776_DACLVOL] ||
		    chip->dac_volume[1] != data->wm8776_regs[WM8776_DACRVOL]) {
			wm8776_write(chip, WM8776_DACMASTER,
				     chip->dac_volume[0] | WM8776_UPDATE);
			data->wm8776_regs[WM8776_DACLVOL] = chip->dac_volume[0];
			data->wm8776_regs[WM8776_DACRVOL] = chip->dac_volume[0];
		}
	} else {
		to_change = (chip->dac_volume[0] !=
			     data->wm8776_regs[WM8776_DACLVOL]) << 0;
		to_change |= (chip->dac_volume[1] !=
			      data->wm8776_regs[WM8776_DACLVOL]) << 1;
		if (to_change & 1)
			wm8776_write(chip, WM8776_DACLVOL, chip->dac_volume[0] |
				     ((to_change & 2) ? 0 : WM8776_UPDATE));
		if (to_change & 2)
			wm8776_write(chip, WM8776_DACRVOL,
				     chip->dac_volume[1] | WM8776_UPDATE);
	}
}