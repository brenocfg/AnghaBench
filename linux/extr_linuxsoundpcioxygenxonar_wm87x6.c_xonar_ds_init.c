#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int anti_pop_delay; int /*<<< orphan*/  output_enable_bit; } ;
struct xonar_wm87x6 {int /*<<< orphan*/  hp_jack; TYPE_1__ generic; } ;
struct oxygen {int /*<<< orphan*/  card; int /*<<< orphan*/  interrupt_mask; struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 int GPIO_DS_HP_DETECT ; 
 int GPIO_DS_INPUT_ROUTE ; 
 int /*<<< orphan*/  GPIO_DS_OUTPUT_ENABLE ; 
 int GPIO_DS_OUTPUT_FRONTLR ; 
 int /*<<< orphan*/  OXYGEN_GPIO_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  OXYGEN_GPIO_INTERRUPT_MASK ; 
 int /*<<< orphan*/  OXYGEN_INT_GPIO ; 
 int /*<<< orphan*/  SND_JACK_HEADPHONE ; 
 int /*<<< orphan*/  oxygen_clear_bits16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oxygen_set_bits16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_component_add (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_jack_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wm8766_init (struct oxygen*) ; 
 int /*<<< orphan*/  wm8776_init (struct oxygen*) ; 
 int /*<<< orphan*/  xonar_ds_handle_hp_jack (struct oxygen*) ; 
 int /*<<< orphan*/  xonar_enable_output (struct oxygen*) ; 

__attribute__((used)) static void xonar_ds_init(struct oxygen *chip)
{
	struct xonar_wm87x6 *data = chip->model_data;

	data->generic.anti_pop_delay = 300;
	data->generic.output_enable_bit = GPIO_DS_OUTPUT_ENABLE;

	wm8776_init(chip);
	wm8766_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL,
			  GPIO_DS_INPUT_ROUTE | GPIO_DS_OUTPUT_FRONTLR);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_CONTROL,
			    GPIO_DS_HP_DETECT);
	oxygen_set_bits16(chip, OXYGEN_GPIO_DATA, GPIO_DS_INPUT_ROUTE);
	oxygen_set_bits16(chip, OXYGEN_GPIO_INTERRUPT_MASK, GPIO_DS_HP_DETECT);
	chip->interrupt_mask |= OXYGEN_INT_GPIO;

	xonar_enable_output(chip);

	snd_jack_new(chip->card, "Headphone",
		     SND_JACK_HEADPHONE, &data->hp_jack, false, false);
	xonar_ds_handle_hp_jack(chip);

	snd_component_add(chip->card, "WM8776");
	snd_component_add(chip->card, "WM8766");
}