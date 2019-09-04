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
struct xonar_pcm179x {int dacs; TYPE_1__ generic; } ;
struct oxygen {int /*<<< orphan*/  card; struct xonar_pcm179x* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM9780_FMIC2MIC ; 
 int /*<<< orphan*/  CM9780_JACK ; 
 int /*<<< orphan*/  GPIO_D2_ALT ; 
 int /*<<< orphan*/  GPIO_D2_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  OXYGEN_GPIO_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  oxygen_ac97_set_bits (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_clear_bits16 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_set_bits16 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm1796_init (struct oxygen*) ; 
 int /*<<< orphan*/  snd_component_add (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xonar_enable_output (struct oxygen*) ; 
 int /*<<< orphan*/  xonar_init_cs53x1 (struct oxygen*) ; 

__attribute__((used)) static void xonar_d2_init(struct oxygen *chip)
{
	struct xonar_pcm179x *data = chip->model_data;

	data->generic.anti_pop_delay = 300;
	data->generic.output_enable_bit = GPIO_D2_OUTPUT_ENABLE;
	data->dacs = 4;

	pcm1796_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL, GPIO_D2_ALT);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA, GPIO_D2_ALT);

	oxygen_ac97_set_bits(chip, 0, CM9780_JACK, CM9780_FMIC2MIC);

	xonar_init_cs53x1(chip);
	xonar_enable_output(chip);

	snd_component_add(chip->card, "PCM1796");
	snd_component_add(chip->card, "CS5381");
}