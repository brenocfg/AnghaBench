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
struct snd_usX2Y_substream {int dummy; } ;
struct snd_pcm {struct snd_usX2Y_substream** private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  usX2Y_audio_stream_free (struct snd_usX2Y_substream**) ; 

__attribute__((used)) static void snd_usX2Y_pcm_private_free(struct snd_pcm *pcm)
{
	struct snd_usX2Y_substream **usX2Y_stream = pcm->private_data;
	if (usX2Y_stream)
		usX2Y_audio_stream_free(usX2Y_stream);
}