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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MADERA_MAX_OUTPUT ; 
 unsigned int MADERA_OUT1_MONO ; 
 int MADERA_OUTPUT_PATH_CONFIG_1L ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,unsigned int,unsigned int) ; 

int madera_set_output_mode(struct snd_soc_component *component, int output,
			   bool differential)
{
	unsigned int reg, val;
	int ret;

	if (output < 1 || output > MADERA_MAX_OUTPUT)
		return -EINVAL;

	reg = MADERA_OUTPUT_PATH_CONFIG_1L + (output - 1) * 8;

	if (differential)
		val = MADERA_OUT1_MONO;
	else
		val = 0;

	ret = snd_soc_component_update_bits(component, reg, MADERA_OUT1_MONO,
					    val);
	if (ret < 0)
		return ret;
	else
		return 0;
}