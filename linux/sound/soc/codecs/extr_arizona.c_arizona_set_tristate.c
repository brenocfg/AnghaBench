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
struct snd_soc_dai {TYPE_1__* driver; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {int base; } ;

/* Variables and functions */
 unsigned int ARIZONA_AIF1_TRI ; 
 scalar_t__ ARIZONA_AIF_RATE_CTRL ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,scalar_t__,unsigned int,unsigned int) ; 

__attribute__((used)) static int arizona_set_tristate(struct snd_soc_dai *dai, int tristate)
{
	struct snd_soc_component *component = dai->component;
	int base = dai->driver->base;
	unsigned int reg;

	if (tristate)
		reg = ARIZONA_AIF1_TRI;
	else
		reg = 0;

	return snd_soc_component_update_bits(component,
					     base + ARIZONA_AIF_RATE_CTRL,
					     ARIZONA_AIF1_TRI, reg);
}