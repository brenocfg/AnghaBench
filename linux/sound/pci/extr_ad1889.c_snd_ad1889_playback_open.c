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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; } ;
struct snd_ad1889 {struct snd_pcm_substream* psubs; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ad1889_playback_hw ; 
 struct snd_ad1889* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int
snd_ad1889_playback_open(struct snd_pcm_substream *ss)
{
	struct snd_ad1889 *chip = snd_pcm_substream_chip(ss);
	struct snd_pcm_runtime *rt = ss->runtime;

	chip->psubs = ss;
	rt->hw = snd_ad1889_playback_hw;

	return 0;
}