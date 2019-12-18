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
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct snd_line6_pcm {int dummy; } ;
struct line6_pcm_stream {int /*<<< orphan*/  pos_done; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 struct line6_pcm_stream* get_stream (struct snd_line6_pcm*,int /*<<< orphan*/ ) ; 
 struct snd_line6_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

snd_pcm_uframes_t snd_line6_pointer(struct snd_pcm_substream *substream)
{
	struct snd_line6_pcm *line6pcm = snd_pcm_substream_chip(substream);
	struct line6_pcm_stream *pstr = get_stream(line6pcm, substream->stream);

	return pstr->pos_done;
}