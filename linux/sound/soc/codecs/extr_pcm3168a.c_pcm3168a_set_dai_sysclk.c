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
struct snd_soc_dai {int /*<<< orphan*/  component; } ;
struct pcm3168a_priv {unsigned int sysclk; int /*<<< orphan*/  scki; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int PCM3168A_MAX_SYSCLK ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 struct pcm3168a_priv* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm3168a_set_dai_sysclk(struct snd_soc_dai *dai,
				  int clk_id, unsigned int freq, int dir)
{
	struct pcm3168a_priv *pcm3168a = snd_soc_component_get_drvdata(dai->component);
	int ret;

	if (freq > PCM3168A_MAX_SYSCLK)
		return -EINVAL;

	ret = clk_set_rate(pcm3168a->scki, freq);
	if (ret)
		return ret;

	pcm3168a->sysclk = freq;

	return 0;
}