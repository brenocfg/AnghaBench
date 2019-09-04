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
struct TYPE_2__ {int /*<<< orphan*/  ext_power_bit; int /*<<< orphan*/  ext_power_int_reg; int /*<<< orphan*/  ext_power_reg; } ;
struct xonar_pcm179x {TYPE_1__ generic; } ;
struct oxygen {struct xonar_pcm179x* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_D2X_EXT_POWER ; 
 int /*<<< orphan*/  OXYGEN_GPIO_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  OXYGEN_GPIO_INTERRUPT_MASK ; 
 int /*<<< orphan*/  oxygen_clear_bits16 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xonar_d2_init (struct oxygen*) ; 
 int /*<<< orphan*/  xonar_init_ext_power (struct oxygen*) ; 

__attribute__((used)) static void xonar_d2x_init(struct oxygen *chip)
{
	struct xonar_pcm179x *data = chip->model_data;

	data->generic.ext_power_reg = OXYGEN_GPIO_DATA;
	data->generic.ext_power_int_reg = OXYGEN_GPIO_INTERRUPT_MASK;
	data->generic.ext_power_bit = GPIO_D2X_EXT_POWER;
	oxygen_clear_bits16(chip, OXYGEN_GPIO_CONTROL, GPIO_D2X_EXT_POWER);
	xonar_init_ext_power(chip);
	xonar_d2_init(chip);
}