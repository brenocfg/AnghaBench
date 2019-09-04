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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;

/* Variables and functions */
 int snd_soc_dai_set_bclk_ratio (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int audioinjector_octo_dai_init(struct snd_soc_pcm_runtime *rtd)
{
	return snd_soc_dai_set_bclk_ratio(rtd->cpu_dai, 64);
}