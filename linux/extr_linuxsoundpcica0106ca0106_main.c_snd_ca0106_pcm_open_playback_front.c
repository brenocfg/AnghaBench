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
 int /*<<< orphan*/  PCM_FRONT_CHANNEL ; 
 int snd_ca0106_pcm_open_playback_channel (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_ca0106_pcm_open_playback_front(struct snd_pcm_substream *substream)
{
	return snd_ca0106_pcm_open_playback_channel(substream, PCM_FRONT_CHANNEL);
}