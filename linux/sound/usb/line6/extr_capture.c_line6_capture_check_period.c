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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int bytes; int period; int /*<<< orphan*/  lock; } ;
struct snd_line6_pcm {TYPE_1__ in; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 struct snd_pcm_substream* get_substream (struct snd_line6_pcm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void line6_capture_check_period(struct snd_line6_pcm *line6pcm, int length)
{
	struct snd_pcm_substream *substream =
	    get_substream(line6pcm, SNDRV_PCM_STREAM_CAPTURE);

	line6pcm->in.bytes += length;
	if (line6pcm->in.bytes >= line6pcm->in.period) {
		line6pcm->in.bytes %= line6pcm->in.period;
		spin_unlock(&line6pcm->in.lock);
		snd_pcm_period_elapsed(substream);
		spin_lock(&line6pcm->in.lock);
	}
}