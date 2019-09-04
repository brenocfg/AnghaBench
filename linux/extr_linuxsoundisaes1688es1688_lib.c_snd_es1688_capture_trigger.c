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
struct snd_es1688 {int dummy; } ;

/* Variables and functions */
 int snd_es1688_trigger (struct snd_es1688*,int,int) ; 
 struct snd_es1688* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_es1688_capture_trigger(struct snd_pcm_substream *substream,
				      int cmd)
{
	struct snd_es1688 *chip = snd_pcm_substream_chip(substream);
	return snd_es1688_trigger(chip, cmd, 0x0f);
}