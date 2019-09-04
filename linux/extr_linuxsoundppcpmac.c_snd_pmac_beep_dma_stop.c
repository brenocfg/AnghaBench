#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* cmds; } ;
struct snd_pmac {TYPE_2__ extra_dma; int /*<<< orphan*/  playback; } ;
struct TYPE_3__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBDMA_STOP ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pmac_dma_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pmac_pcm_set_format (struct snd_pmac*) ; 

void snd_pmac_beep_dma_stop(struct snd_pmac *chip)
{
	snd_pmac_dma_stop(&chip->playback);
	chip->extra_dma.cmds->command = cpu_to_le16(DBDMA_STOP);
	snd_pmac_pcm_set_format(chip); /* reset format */
}