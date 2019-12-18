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
struct oxygen {int dummy; } ;

/* Variables and functions */
 unsigned int GPIO_CS53x1_M_DOUBLE ; 
 int /*<<< orphan*/  GPIO_CS53x1_M_MASK ; 
 unsigned int GPIO_CS53x1_M_QUAD ; 
 unsigned int GPIO_CS53x1_M_SINGLE ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  oxygen_write16_masked (struct oxygen*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 

void xonar_set_cs53x1_params(struct oxygen *chip,
			     struct snd_pcm_hw_params *params)
{
	unsigned int value;

	if (params_rate(params) <= 54000)
		value = GPIO_CS53x1_M_SINGLE;
	else if (params_rate(params) <= 108000)
		value = GPIO_CS53x1_M_DOUBLE;
	else
		value = GPIO_CS53x1_M_QUAD;
	oxygen_write16_masked(chip, OXYGEN_GPIO_DATA,
			      value, GPIO_CS53x1_M_MASK);
}