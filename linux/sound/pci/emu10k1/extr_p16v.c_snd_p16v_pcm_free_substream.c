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
struct snd_pcm_runtime {struct snd_emu10k1_pcm* private_data; } ;
struct snd_emu10k1_pcm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_emu10k1_pcm*) ; 

__attribute__((used)) static void snd_p16v_pcm_free_substream(struct snd_pcm_runtime *runtime)
{
	struct snd_emu10k1_pcm *epcm = runtime->private_data;

	kfree(epcm);
}