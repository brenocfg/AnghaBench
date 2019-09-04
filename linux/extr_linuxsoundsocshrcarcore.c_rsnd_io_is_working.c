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
struct rsnd_dai_stream {scalar_t__ substream; } ;

/* Variables and functions */
 int snd_pcm_running (scalar_t__) ; 

int rsnd_io_is_working(struct rsnd_dai_stream *io)
{
	/* see rsnd_dai_stream_init/quit() */
	if (io->substream)
		return snd_pcm_running(io->substream);

	return 0;
}