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
struct snd_tscm {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rx_stream; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; struct snd_tscm* private_data; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_pcm_prepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_tscm_stream_start_duplex (struct snd_tscm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm_playback_prepare(struct snd_pcm_substream *substream)
{
	struct snd_tscm *tscm = substream->private_data;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	mutex_lock(&tscm->mutex);

	err = snd_tscm_stream_start_duplex(tscm, runtime->rate);
	if (err >= 0)
		amdtp_stream_pcm_prepare(&tscm->rx_stream);

	mutex_unlock(&tscm->mutex);

	return err;
}