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
struct snd_trident_voice {struct snd_trident_voice* extra; } ;
struct snd_trident {int dummy; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_trident_voice* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct snd_trident* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_trident_free_voice (struct snd_trident*,struct snd_trident_voice*) ; 

__attribute__((used)) static int snd_trident_si7018_capture_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_trident *trident = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_trident_voice *voice = runtime->private_data;
	struct snd_trident_voice *evoice = voice ? voice->extra : NULL;

	snd_pcm_lib_free_pages(substream);
	if (evoice != NULL) {
		snd_trident_free_voice(trident, evoice);
		voice->extra = NULL;
	}
	return 0;
}