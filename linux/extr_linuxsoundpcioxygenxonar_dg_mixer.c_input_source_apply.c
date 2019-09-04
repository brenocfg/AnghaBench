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
struct dg {scalar_t__ input_sel; int /*<<< orphan*/ * cs4245_shadow; } ;

/* Variables and functions */
 scalar_t__ CAPTURE_SRC_FP_MIC ; 
 scalar_t__ CAPTURE_SRC_LINE ; 
 scalar_t__ CAPTURE_SRC_MIC ; 
 size_t CS4245_ANALOG_IN ; 
 int /*<<< orphan*/  CS4245_SEL_INPUT_1 ; 
 int /*<<< orphan*/  CS4245_SEL_INPUT_2 ; 
 int /*<<< orphan*/  CS4245_SEL_INPUT_4 ; 
 int /*<<< orphan*/  CS4245_SEL_MASK ; 
 int cs4245_write_spi (struct oxygen*,size_t) ; 

__attribute__((used)) static int input_source_apply(struct oxygen *chip)
{
	struct dg *data = chip->model_data;

	data->cs4245_shadow[CS4245_ANALOG_IN] &= ~CS4245_SEL_MASK;
	if (data->input_sel == CAPTURE_SRC_FP_MIC)
		data->cs4245_shadow[CS4245_ANALOG_IN] |= CS4245_SEL_INPUT_2;
	else if (data->input_sel == CAPTURE_SRC_LINE)
		data->cs4245_shadow[CS4245_ANALOG_IN] |= CS4245_SEL_INPUT_4;
	else if (data->input_sel != CAPTURE_SRC_MIC)
		data->cs4245_shadow[CS4245_ANALOG_IN] |= CS4245_SEL_INPUT_1;
	return cs4245_write_spi(chip, CS4245_ANALOG_IN);
}