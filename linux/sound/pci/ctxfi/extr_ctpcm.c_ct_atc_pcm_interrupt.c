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
struct ct_atc_pcm {int /*<<< orphan*/  substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ct_atc_pcm_interrupt(struct ct_atc_pcm *atc_pcm)
{
	struct ct_atc_pcm *apcm = atc_pcm;

	if (!apcm->substream)
		return;

	snd_pcm_period_elapsed(apcm->substream);
}