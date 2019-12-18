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
struct snd_pmac {int control_mask; int rate_index; scalar_t__ format; int /*<<< orphan*/  (* set_format ) (struct snd_pmac*) ;TYPE_1__* awacs; } ;
struct TYPE_2__ {int /*<<< orphan*/  byteswap; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_FORMAT_S16_LE ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct snd_pmac*) ; 

__attribute__((used)) static void snd_pmac_pcm_set_format(struct snd_pmac *chip)
{
	/* set up frequency and format */
	out_le32(&chip->awacs->control, chip->control_mask | (chip->rate_index << 8));
	out_le32(&chip->awacs->byteswap, chip->format == SNDRV_PCM_FORMAT_S16_LE ? 1 : 0);
	if (chip->set_format)
		chip->set_format(chip);
}