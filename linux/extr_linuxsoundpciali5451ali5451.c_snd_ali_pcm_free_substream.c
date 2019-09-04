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
struct snd_pcm_runtime {struct snd_ali_voice* private_data; } ;
struct snd_ali_voice {int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ali_free_voice (int /*<<< orphan*/ ,struct snd_ali_voice*) ; 

__attribute__((used)) static void snd_ali_pcm_free_substream(struct snd_pcm_runtime *runtime)
{
	struct snd_ali_voice *pvoice = runtime->private_data;

	if (pvoice)
		snd_ali_free_voice(pvoice->codec, pvoice);
}