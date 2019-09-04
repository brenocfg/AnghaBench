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
typedef  int /*<<< orphan*/  u32 ;
struct bcm2835_chip {int dummy; } ;
typedef  enum snd_bcm2835_route { ____Placeholder_snd_bcm2835_route } snd_bcm2835_route ;

/* Variables and functions */
 int snd_bcm2835_new_pcm (struct bcm2835_chip*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm2835_audio_simple_newpcm(struct bcm2835_chip *chip,
				       const char *name,
				       enum snd_bcm2835_route route,
				       u32 numchannels)
{
	return snd_bcm2835_new_pcm(chip, name, 0, route, numchannels, false);
}