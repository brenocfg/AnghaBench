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
struct rme96 {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 struct rme96* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_rme96_playback_ptr (struct rme96*) ; 

__attribute__((used)) static snd_pcm_uframes_t
snd_rme96_playback_pointer(struct snd_pcm_substream *substream)
{
	struct rme96 *rme96 = snd_pcm_substream_chip(substream);
	return snd_rme96_playback_ptr(rme96);
}