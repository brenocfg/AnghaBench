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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; struct snd_ff* private_data; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  rate; } ;
struct snd_ff {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_pcm_prepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_ff_stream_start_duplex (struct snd_ff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm_playback_prepare(struct snd_pcm_substream *substream)
{
	struct snd_ff *ff = substream->private_data;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	mutex_lock(&ff->mutex);

	err = snd_ff_stream_start_duplex(ff, runtime->rate);
	if (err >= 0)
		amdtp_stream_pcm_prepare(&ff->rx_stream);

	mutex_unlock(&ff->mutex);

	return err;
}