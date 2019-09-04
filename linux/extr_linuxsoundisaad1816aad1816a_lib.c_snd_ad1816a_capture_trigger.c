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
struct snd_ad1816a {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1816A_CAPTURE_ENABLE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int snd_ad1816a_trigger (struct snd_ad1816a*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct snd_ad1816a* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_ad1816a_capture_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_ad1816a *chip = snd_pcm_substream_chip(substream);
	return snd_ad1816a_trigger(chip, AD1816A_CAPTURE_ENABLE,
				   SNDRV_PCM_STREAM_CAPTURE, cmd, 1);
}