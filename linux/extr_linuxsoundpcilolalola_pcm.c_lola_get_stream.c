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
struct snd_pcm_substream {unsigned int number; } ;
struct lola_stream {int dummy; } ;
struct lola_pcm {struct lola_stream* streams; } ;

/* Variables and functions */
 struct lola_pcm* lola_get_pcm (struct snd_pcm_substream*) ; 

__attribute__((used)) static struct lola_stream *lola_get_stream(struct snd_pcm_substream *substream)
{
	struct lola_pcm *pcm = lola_get_pcm(substream);
	unsigned int idx = substream->number;
	return &pcm->streams[idx];
}