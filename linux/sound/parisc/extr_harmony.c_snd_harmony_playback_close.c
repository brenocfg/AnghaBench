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
struct snd_harmony {int /*<<< orphan*/ * psubs; } ;

/* Variables and functions */
 struct snd_harmony* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int 
snd_harmony_playback_close(struct snd_pcm_substream *ss)
{
	struct snd_harmony *h = snd_pcm_substream_chip(ss);
	h->psubs = NULL;
	return 0;
}