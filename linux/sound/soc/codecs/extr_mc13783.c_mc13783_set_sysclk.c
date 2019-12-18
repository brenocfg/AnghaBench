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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 unsigned int AUDIO_CLK (int) ; 
 unsigned int AUDIO_CLK_SEL ; 
 int EINVAL ; 
 int MC13783_CLK_CLIB ; 
 unsigned int* mc13783_sysclk ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int mc13783_set_sysclk(struct snd_soc_dai *dai,
				  int clk_id, unsigned int freq, int dir,
				  unsigned int reg)
{
	struct snd_soc_component *component = dai->component;
	int clk;
	unsigned int val = 0;
	unsigned int mask = AUDIO_CLK(0x7) | AUDIO_CLK_SEL;

	for (clk = 0; clk < ARRAY_SIZE(mc13783_sysclk); clk++) {
		if (mc13783_sysclk[clk] < 0)
			continue;
		if (mc13783_sysclk[clk] == freq)
			break;
	}

	if (clk == ARRAY_SIZE(mc13783_sysclk))
		return -EINVAL;

	if (clk_id == MC13783_CLK_CLIB)
		val |= AUDIO_CLK_SEL;

	val |= AUDIO_CLK(clk);

	snd_soc_component_update_bits(component, reg, mask, val);

	return 0;
}