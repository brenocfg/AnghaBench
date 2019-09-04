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
struct snd_pcm_substream {size_t stream; } ;
struct lola_pcm {int dummy; } ;
struct lola {struct lola_pcm* pcm; } ;

/* Variables and functions */
 struct lola* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static struct lola_pcm *lola_get_pcm(struct snd_pcm_substream *substream)
{
	struct lola *chip = snd_pcm_substream_chip(substream);
	return &chip->pcm[substream->stream];
}