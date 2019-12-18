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
struct snd_pcm_substream {int dummy; } ;
struct rme96 {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ RME96_IO_PLAY_BUFFER ; 
 int /*<<< orphan*/  memset_io (scalar_t__,int /*<<< orphan*/ ,unsigned long) ; 
 struct rme96* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int
snd_rme96_playback_silence(struct snd_pcm_substream *substream,
			   int channel, unsigned long pos, unsigned long count)
{
	struct rme96 *rme96 = snd_pcm_substream_chip(substream);

	memset_io(rme96->iobase + RME96_IO_PLAY_BUFFER + pos,
		  0, count);
	return 0;
}