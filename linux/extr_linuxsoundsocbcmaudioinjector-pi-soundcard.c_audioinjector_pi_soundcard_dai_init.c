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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  codec_dai; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  WM8731_SYSCLK_XTAL ; 
 int snd_soc_dai_set_sysclk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audioinjector_pi_soundcard_dai_init(struct snd_soc_pcm_runtime *rtd)
{
	return snd_soc_dai_set_sysclk(rtd->codec_dai, WM8731_SYSCLK_XTAL, 12000000, SND_SOC_CLOCK_IN);
}