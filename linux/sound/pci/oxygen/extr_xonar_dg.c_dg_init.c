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
struct oxygen {struct dg* model_data; } ;
struct dg {int /*<<< orphan*/  input_sel; int /*<<< orphan*/  output_sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPTURE_SRC_MIC ; 
 int GPIO_HP_REAR ; 
 int GPIO_INPUT_ROUTE ; 
 int GPIO_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  OXYGEN_GPIO_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  PLAYBACK_DST_HP_FP ; 
 int /*<<< orphan*/  cs4245_init (struct oxygen*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  oxygen_write16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 

void dg_init(struct oxygen *chip)
{
	struct dg *data = chip->model_data;

	data->output_sel = PLAYBACK_DST_HP_FP;
	data->input_sel = CAPTURE_SRC_MIC;

	cs4245_init(chip);
	oxygen_write16(chip, OXYGEN_GPIO_CONTROL,
		       GPIO_OUTPUT_ENABLE | GPIO_HP_REAR | GPIO_INPUT_ROUTE);
	/* anti-pop delay, wait some time before enabling the output */
	msleep(2500);
	oxygen_write16(chip, OXYGEN_GPIO_DATA,
		       GPIO_OUTPUT_ENABLE | GPIO_INPUT_ROUTE);
}