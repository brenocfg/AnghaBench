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
struct snd_pcm_substream {struct snd_dg00x* private_data; } ;
struct snd_dg00x {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_dot_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdtp_stream_pcm_prepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_dg00x_stream_start_duplex (struct snd_dg00x*) ; 

__attribute__((used)) static int pcm_playback_prepare(struct snd_pcm_substream *substream)
{
	struct snd_dg00x *dg00x = substream->private_data;
	int err;

	mutex_lock(&dg00x->mutex);

	err = snd_dg00x_stream_start_duplex(dg00x);
	if (err >= 0) {
		amdtp_stream_pcm_prepare(&dg00x->rx_stream);
		amdtp_dot_reset(&dg00x->rx_stream);
	}

	mutex_unlock(&dg00x->mutex);

	return err;
}