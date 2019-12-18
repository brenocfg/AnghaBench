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
struct line6_pcm_stream {int dummy; } ;
struct snd_line6_pcm {struct line6_pcm_stream in; struct line6_pcm_stream out; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_PLAYBACK ; 

__attribute__((used)) static inline struct line6_pcm_stream *
get_stream(struct snd_line6_pcm *line6pcm, int direction)
{
	return (direction == SNDRV_PCM_STREAM_PLAYBACK) ?
		&line6pcm->out : &line6pcm->in;
}