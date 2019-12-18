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
struct snd_pcm_hw_params {int dummy; } ;
struct oxygen {struct generic_data* model_data; } ;
struct generic_data {unsigned int* wm8785_regs; } ;

/* Variables and functions */
 unsigned int WM8785_FORMAT_LJUST ; 
 unsigned int WM8785_MCR_SLAVE ; 
 unsigned int WM8785_OSR_DOUBLE ; 
 unsigned int WM8785_OSR_QUAD ; 
 unsigned int WM8785_OSR_SINGLE ; 
 int /*<<< orphan*/  WM8785_R0 ; 
 int /*<<< orphan*/  WM8785_R2 ; 
 int /*<<< orphan*/  WM8785_R7 ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  wm8785_write (struct oxygen*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void set_wm8785_params(struct oxygen *chip,
			      struct snd_pcm_hw_params *params)
{
	struct generic_data *data = chip->model_data;
	unsigned int value;

	value = WM8785_MCR_SLAVE | WM8785_FORMAT_LJUST;
	if (params_rate(params) <= 48000)
		value |= WM8785_OSR_SINGLE;
	else if (params_rate(params) <= 96000)
		value |= WM8785_OSR_DOUBLE;
	else
		value |= WM8785_OSR_QUAD;
	if (value != data->wm8785_regs[0]) {
		wm8785_write(chip, WM8785_R7, 0);
		wm8785_write(chip, WM8785_R0, value);
		wm8785_write(chip, WM8785_R2, data->wm8785_regs[2]);
	}
}