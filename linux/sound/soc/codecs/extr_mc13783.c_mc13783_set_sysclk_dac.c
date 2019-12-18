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
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC13783_AUDIO_DAC ; 
 int mc13783_set_sysclk (struct snd_soc_dai*,int,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mc13783_set_sysclk_dac(struct snd_soc_dai *dai,
				  int clk_id, unsigned int freq, int dir)
{
	return mc13783_set_sysclk(dai, clk_id, freq, dir, MC13783_AUDIO_DAC);
}