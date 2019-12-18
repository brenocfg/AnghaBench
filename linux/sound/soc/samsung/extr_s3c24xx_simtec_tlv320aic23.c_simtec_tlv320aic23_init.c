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
struct snd_soc_pcm_runtime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  simtec_audio_init (struct snd_soc_pcm_runtime*) ; 

__attribute__((used)) static int simtec_tlv320aic23_init(struct snd_soc_pcm_runtime *rtd)
{
	simtec_audio_init(rtd);

	return 0;
}