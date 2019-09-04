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

/* Variables and functions */
 int snd_bcm2835_playback_open_generic (struct snd_pcm_substream*,int) ; 

__attribute__((used)) static int snd_bcm2835_playback_spdif_open(struct snd_pcm_substream *substream)
{
	return snd_bcm2835_playback_open_generic(substream, 1);
}