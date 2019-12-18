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
struct snd_motu {int /*<<< orphan*/  rx_stream; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_stream_pcm_pointer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static snd_pcm_uframes_t playback_pointer(struct snd_pcm_substream *substream)
{
	struct snd_motu *motu = substream->private_data;

	return amdtp_stream_pcm_pointer(&motu->rx_stream);
}