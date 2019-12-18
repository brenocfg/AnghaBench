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
struct snd_pcm_substream {TYPE_1__* pcm; struct snd_dice* private_data; } ;
struct snd_dice {struct amdtp_stream* rx_stream; } ;
struct amdtp_stream {int dummy; } ;
struct TYPE_2__ {size_t device; } ;

/* Variables and functions */
 int amdtp_stream_pcm_ack (struct amdtp_stream*) ; 

__attribute__((used)) static int playback_ack(struct snd_pcm_substream *substream)
{
	struct snd_dice *dice = substream->private_data;
	struct amdtp_stream *stream = &dice->rx_stream[substream->pcm->device];

	return amdtp_stream_pcm_ack(stream);
}