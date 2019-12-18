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
struct nm256_stream {scalar_t__ substream; scalar_t__ running; } ;
struct nm256 {int /*<<< orphan*/  reg_lock; struct nm256_stream* streams; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  snd_nm256_capture_mark (struct nm256*,struct nm256_stream*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
snd_nm256_capture_update(struct nm256 *chip)
{
	struct nm256_stream *s;

	s = &chip->streams[SNDRV_PCM_STREAM_CAPTURE];
	if (s->running && s->substream) {
		spin_unlock(&chip->reg_lock);
		snd_pcm_period_elapsed(s->substream);
		spin_lock(&chip->reg_lock);
		snd_nm256_capture_mark(chip, s);
	}
}