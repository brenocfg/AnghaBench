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
struct xonar_wm87x6 {unsigned int* wm8766_regs; int /*<<< orphan*/  hp_jack; } ;
struct oxygen {int /*<<< orphan*/  mutex; struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 int GPIO_DS_HP_DETECT ; 
 int /*<<< orphan*/  GPIO_DS_OUTPUT_FRONTLR ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  SND_JACK_HEADPHONE ; 
 size_t WM8766_DAC_CTRL ; 
 unsigned int WM8766_MUTEALL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int oxygen_read16 (struct oxygen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_write16_masked (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_jack_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8766_write_cached (struct oxygen*,size_t,unsigned int) ; 

__attribute__((used)) static void xonar_ds_handle_hp_jack(struct oxygen *chip)
{
	struct xonar_wm87x6 *data = chip->model_data;
	bool hp_plugged;
	unsigned int reg;

	mutex_lock(&chip->mutex);

	hp_plugged = !(oxygen_read16(chip, OXYGEN_GPIO_DATA) &
		       GPIO_DS_HP_DETECT);

	oxygen_write16_masked(chip, OXYGEN_GPIO_DATA,
			      hp_plugged ? 0 : GPIO_DS_OUTPUT_FRONTLR,
			      GPIO_DS_OUTPUT_FRONTLR);

	reg = data->wm8766_regs[WM8766_DAC_CTRL] & ~WM8766_MUTEALL;
	if (hp_plugged)
		reg |= WM8766_MUTEALL;
	wm8766_write_cached(chip, WM8766_DAC_CTRL, reg);

	snd_jack_report(data->hp_jack, hp_plugged ? SND_JACK_HEADPHONE : 0);

	mutex_unlock(&chip->mutex);
}