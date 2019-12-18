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
struct snd_pcm_substream {struct snd_bebob* private_data; } ;
struct snd_bebob {int /*<<< orphan*/  tx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_pcm_prepare (int /*<<< orphan*/ *) ; 
 int snd_bebob_stream_start_duplex (struct snd_bebob*) ; 

__attribute__((used)) static int
pcm_capture_prepare(struct snd_pcm_substream *substream)
{
	struct snd_bebob *bebob = substream->private_data;
	int err;

	err = snd_bebob_stream_start_duplex(bebob);
	if (err >= 0)
		amdtp_stream_pcm_prepare(&bebob->tx_stream);

	return err;
}