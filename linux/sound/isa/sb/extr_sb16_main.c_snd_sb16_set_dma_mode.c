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
struct snd_sb {scalar_t__ dma8; scalar_t__ dma16; scalar_t__ force_mode16; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SB_MODE_CAPTURE_16 ; 
 scalar_t__ SB_MODE_PLAYBACK_16 ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static int snd_sb16_set_dma_mode(struct snd_sb *chip, int what)
{
	if (chip->dma8 < 0 || chip->dma16 < 0) {
		if (snd_BUG_ON(what))
			return -EINVAL;
		return 0;
	}
	if (what == 0) {
		chip->force_mode16 = 0;
	} else if (what == 1) {
		chip->force_mode16 = SB_MODE_PLAYBACK_16;
	} else if (what == 2) {
		chip->force_mode16 = SB_MODE_CAPTURE_16;
	} else {
		return -EINVAL;
	}
	return 0;
}