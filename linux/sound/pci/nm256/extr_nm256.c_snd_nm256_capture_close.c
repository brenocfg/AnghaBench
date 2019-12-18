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
struct nm256 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_nm256_release_irq (struct nm256*) ; 
 struct nm256* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int
snd_nm256_capture_close(struct snd_pcm_substream *substream)
{
	struct nm256 *chip = snd_pcm_substream_chip(substream);

	snd_nm256_release_irq(chip);
	return 0;
}