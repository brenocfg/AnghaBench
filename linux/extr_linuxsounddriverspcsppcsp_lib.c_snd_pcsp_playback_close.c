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
struct snd_pcsp {int /*<<< orphan*/ * playback_substream; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcsp_sync_stop (struct snd_pcsp*) ; 
 struct snd_pcsp* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcsp_playback_close(struct snd_pcm_substream *substream)
{
	struct snd_pcsp *chip = snd_pcm_substream_chip(substream);
#if PCSP_DEBUG
	printk(KERN_INFO "PCSP: close called\n");
#endif
	pcsp_sync_stop(chip);
	chip->playback_substream = NULL;
	return 0;
}