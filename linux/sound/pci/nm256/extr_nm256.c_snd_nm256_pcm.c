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
struct snd_pcm {scalar_t__ info_flags; struct nm256* private_data; } ;
struct nm256_stream {scalar_t__ buf; scalar_t__ bufptr_addr; scalar_t__ bufptr; } ;
struct nm256 {struct snd_pcm* pcm; TYPE_1__* card; scalar_t__ buffer_start; scalar_t__ buffer_addr; scalar_t__ buffer; struct nm256_stream* streams; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_nm256_capture_ops ; 
 int /*<<< orphan*/  snd_nm256_playback_ops ; 
 int snd_pcm_new (TYPE_1__*,int /*<<< orphan*/ ,int,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_nm256_pcm(struct nm256 *chip, int device)
{
	struct snd_pcm *pcm;
	int i, err;

	for (i = 0; i < 2; i++) {
		struct nm256_stream *s = &chip->streams[i];
		s->bufptr = chip->buffer + (s->buf - chip->buffer_start);
		s->bufptr_addr = chip->buffer_addr + (s->buf - chip->buffer_start);
	}

	err = snd_pcm_new(chip->card, chip->card->driver, device,
			  1, 1, &pcm);
	if (err < 0)
		return err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_nm256_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_nm256_capture_ops);

	pcm->private_data = chip;
	pcm->info_flags = 0;
	chip->pcm = pcm;

	return 0;
}