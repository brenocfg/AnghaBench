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
struct ssi_priv {unsigned int sysclk; } ;
struct snd_soc_dai {size_t id; } ;

/* Variables and functions */
 struct ssi_priv* ssi_cpu_data ; 

__attribute__((used)) static int ssi_set_sysclk(struct snd_soc_dai *cpu_dai, int clk_id,
			  unsigned int freq, int dir)
{
	struct ssi_priv *ssi = &ssi_cpu_data[cpu_dai->id];

	ssi->sysclk = freq;

	return 0;
}