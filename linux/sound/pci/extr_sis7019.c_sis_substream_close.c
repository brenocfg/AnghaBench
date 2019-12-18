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
struct voice {int dummy; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct voice* private_data; } ;
struct sis7019 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sis_free_voice (struct sis7019*,struct voice*) ; 
 struct sis7019* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int sis_substream_close(struct snd_pcm_substream *substream)
{
	struct sis7019 *sis = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct voice *voice = runtime->private_data;

	sis_free_voice(sis, voice);
	return 0;
}