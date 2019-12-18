#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {int /*<<< orphan*/  private_data; } ;
struct snd_cmi8330 {TYPE_1__* streams; } ;
struct TYPE_2__ {int (* open ) (struct snd_pcm_substream*) ;int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 struct snd_cmi8330* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int stub1 (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cmi8330_capture_open(struct snd_pcm_substream *substream)
{
	struct snd_cmi8330 *chip = snd_pcm_substream_chip(substream);

	/* replace the private_data and call the original open callback */
	substream->private_data = chip->streams[SNDRV_PCM_STREAM_CAPTURE].private_data;
	return chip->streams[SNDRV_PCM_STREAM_CAPTURE].open(substream);
}