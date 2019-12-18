#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int anti_pop_delay; int /*<<< orphan*/  ext_power_bit; int /*<<< orphan*/  ext_power_int_reg; int /*<<< orphan*/  ext_power_reg; int /*<<< orphan*/  output_enable_bit; } ;
struct TYPE_5__ {int dacs; int h6; TYPE_1__ generic; } ;
struct xonar_hdav {int /*<<< orphan*/  hdmi; TYPE_2__ pcm179x; } ;
struct TYPE_6__ {int dac_channels_mixer; } ;
struct oxygen {int /*<<< orphan*/  card; TYPE_3__ model; struct xonar_hdav* model_data; } ;

/* Variables and functions */
 int GPIO_HDAV_MAGIC ; 
 int /*<<< orphan*/  GPIO_HDAV_OUTPUT_ENABLE ; 
 int GPIO_INPUT_ROUTE ; 
 int /*<<< orphan*/  GPI_EXT_POWER ; 
 int /*<<< orphan*/  OXYGEN_2WIRE_BUS_STATUS ; 
 int OXYGEN_2WIRE_INTERRUPT_MASK ; 
 int OXYGEN_2WIRE_LENGTH_8 ; 
 int OXYGEN_2WIRE_SPEED_STANDARD ; 
 int /*<<< orphan*/  OXYGEN_GPIO_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  OXYGEN_GPI_DATA ; 
 int /*<<< orphan*/  OXYGEN_GPI_INTERRUPT_MASK ; 
 int /*<<< orphan*/  oxygen_clear_bits16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oxygen_set_bits16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oxygen_write16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcm1796_init (struct oxygen*) ; 
 int /*<<< orphan*/  snd_component_add (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xonar_enable_output (struct oxygen*) ; 
 int /*<<< orphan*/  xonar_hdmi_init (struct oxygen*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xonar_init_cs53x1 (struct oxygen*) ; 
 int /*<<< orphan*/  xonar_init_ext_power (struct oxygen*) ; 

__attribute__((used)) static void xonar_hdav_init(struct oxygen *chip)
{
	struct xonar_hdav *data = chip->model_data;

	oxygen_write16(chip, OXYGEN_2WIRE_BUS_STATUS,
		       OXYGEN_2WIRE_LENGTH_8 |
		       OXYGEN_2WIRE_INTERRUPT_MASK |
		       OXYGEN_2WIRE_SPEED_STANDARD);

	data->pcm179x.generic.anti_pop_delay = 100;
	data->pcm179x.generic.output_enable_bit = GPIO_HDAV_OUTPUT_ENABLE;
	data->pcm179x.generic.ext_power_reg = OXYGEN_GPI_DATA;
	data->pcm179x.generic.ext_power_int_reg = OXYGEN_GPI_INTERRUPT_MASK;
	data->pcm179x.generic.ext_power_bit = GPI_EXT_POWER;
	data->pcm179x.dacs = chip->model.dac_channels_mixer / 2;
	data->pcm179x.h6 = chip->model.dac_channels_mixer > 2;

	pcm1796_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL,
			  GPIO_HDAV_MAGIC | GPIO_INPUT_ROUTE);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA, GPIO_INPUT_ROUTE);

	xonar_init_cs53x1(chip);
	xonar_init_ext_power(chip);
	xonar_hdmi_init(chip, &data->hdmi);
	xonar_enable_output(chip);

	snd_component_add(chip->card, "PCM1796");
	snd_component_add(chip->card, "CS5381");
}