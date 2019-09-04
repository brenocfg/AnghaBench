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
struct snd_m3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_m3_capture ; 
 int snd_m3_substream_open (struct snd_m3*,struct snd_pcm_substream*) ; 
 struct snd_m3* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int
snd_m3_capture_open(struct snd_pcm_substream *subs)
{
	struct snd_m3 *chip = snd_pcm_substream_chip(subs);
	struct snd_pcm_runtime *runtime = subs->runtime;
	int err;

	if ((err = snd_m3_substream_open(chip, subs)) < 0)
		return err;

	runtime->hw = snd_m3_capture;

	return 0;
}