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
struct snd_amd7930 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD7930_FLAG_PLAYBACK ; 
 int snd_amd7930_trigger (struct snd_amd7930*,int /*<<< orphan*/ ,int) ; 
 struct snd_amd7930* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_amd7930_playback_trigger(struct snd_pcm_substream *substream,
					int cmd)
{
	struct snd_amd7930 *amd = snd_pcm_substream_chip(substream);
	return snd_amd7930_trigger(amd, AMD7930_FLAG_PLAYBACK, cmd);
}