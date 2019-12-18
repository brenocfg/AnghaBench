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
struct snd_pcm_substream {struct snd_motu* private_data; } ;
struct snd_motu {int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_pcm_prepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_motu_stream_start_duplex (struct snd_motu*) ; 

__attribute__((used)) static int capture_prepare(struct snd_pcm_substream *substream)
{
	struct snd_motu *motu = substream->private_data;
	int err;

	mutex_lock(&motu->mutex);
	err = snd_motu_stream_start_duplex(motu);
	mutex_unlock(&motu->mutex);
	if (err >= 0)
		amdtp_stream_pcm_prepare(&motu->tx_stream);

	return 0;
}