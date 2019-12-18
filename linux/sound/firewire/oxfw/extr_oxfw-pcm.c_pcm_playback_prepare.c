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
struct snd_pcm_substream {struct snd_oxfw* private_data; } ;
struct snd_oxfw {int /*<<< orphan*/  rx_stream; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_pcm_prepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_oxfw_stream_start_duplex (struct snd_oxfw*) ; 

__attribute__((used)) static int pcm_playback_prepare(struct snd_pcm_substream *substream)
{
	struct snd_oxfw *oxfw = substream->private_data;
	int err;

	mutex_lock(&oxfw->mutex);
	err = snd_oxfw_stream_start_duplex(oxfw);
	mutex_unlock(&oxfw->mutex);
	if (err < 0)
		goto end;

	amdtp_stream_pcm_prepare(&oxfw->rx_stream);
end:
	return err;
}