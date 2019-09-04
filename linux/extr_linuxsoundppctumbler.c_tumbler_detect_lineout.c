#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pmac {struct pmac_tumbler* mixer_data; } ;
struct TYPE_2__ {scalar_t__ addr; } ;
struct pmac_tumbler {TYPE_1__ line_detect; } ;

/* Variables and functions */
 int read_audio_gpio (TYPE_1__*) ; 

__attribute__((used)) static int tumbler_detect_lineout(struct snd_pmac *chip)
{
	struct pmac_tumbler *mix = chip->mixer_data;
	int detect = 0;

	if (mix->line_detect.addr)
		detect |= read_audio_gpio(&mix->line_detect);
	return detect;
}