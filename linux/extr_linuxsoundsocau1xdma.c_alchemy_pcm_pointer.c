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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct audio_stream {TYPE_1__* buffer; int /*<<< orphan*/  dma; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_2__ {long relative_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,long) ; 
 long get_dma_residue (int /*<<< orphan*/ ) ; 
 struct audio_stream* ss_to_as (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t alchemy_pcm_pointer(struct snd_pcm_substream *ss)
{
	struct audio_stream *stream = ss_to_as(ss);
	long location;

	location = get_dma_residue(stream->dma);
	location = stream->buffer->relative_end - location;
	if (location == -1)
		location = 0;
	return bytes_to_frames(ss->runtime, location);
}