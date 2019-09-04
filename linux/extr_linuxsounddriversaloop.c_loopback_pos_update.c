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
struct loopback_pcm {unsigned long last_jiffies; unsigned int last_drift; } ;
struct loopback_cable {unsigned int running; unsigned int pause; struct loopback_pcm** streams; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 unsigned int bytepos_delta (struct loopback_pcm*,unsigned long) ; 
 int /*<<< orphan*/  bytepos_finish (struct loopback_pcm*,unsigned int) ; 
 int /*<<< orphan*/  clear_capture_buf (struct loopback_pcm*,unsigned int) ; 
 int /*<<< orphan*/  copy_play_buf (struct loopback_pcm*,struct loopback_pcm*,unsigned int) ; 
 unsigned long jiffies ; 

__attribute__((used)) static unsigned int loopback_pos_update(struct loopback_cable *cable)
{
	struct loopback_pcm *dpcm_play =
			cable->streams[SNDRV_PCM_STREAM_PLAYBACK];
	struct loopback_pcm *dpcm_capt =
			cable->streams[SNDRV_PCM_STREAM_CAPTURE];
	unsigned long delta_play = 0, delta_capt = 0;
	unsigned int running, count1, count2;

	running = cable->running ^ cable->pause;
	if (running & (1 << SNDRV_PCM_STREAM_PLAYBACK)) {
		delta_play = jiffies - dpcm_play->last_jiffies;
		dpcm_play->last_jiffies += delta_play;
	}

	if (running & (1 << SNDRV_PCM_STREAM_CAPTURE)) {
		delta_capt = jiffies - dpcm_capt->last_jiffies;
		dpcm_capt->last_jiffies += delta_capt;
	}

	if (delta_play == 0 && delta_capt == 0)
		goto unlock;
		
	if (delta_play > delta_capt) {
		count1 = bytepos_delta(dpcm_play, delta_play - delta_capt);
		bytepos_finish(dpcm_play, count1);
		delta_play = delta_capt;
	} else if (delta_play < delta_capt) {
		count1 = bytepos_delta(dpcm_capt, delta_capt - delta_play);
		clear_capture_buf(dpcm_capt, count1);
		bytepos_finish(dpcm_capt, count1);
		delta_capt = delta_play;
	}

	if (delta_play == 0 && delta_capt == 0)
		goto unlock;

	/* note delta_capt == delta_play at this moment */
	count1 = bytepos_delta(dpcm_play, delta_play);
	count2 = bytepos_delta(dpcm_capt, delta_capt);
	if (count1 < count2) {
		dpcm_capt->last_drift = count2 - count1;
		count1 = count2;
	} else if (count1 > count2) {
		dpcm_play->last_drift = count1 - count2;
	}
	copy_play_buf(dpcm_play, dpcm_capt, count1);
	bytepos_finish(dpcm_play, count1);
	bytepos_finish(dpcm_capt, count1);
 unlock:
	return running;
}