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
struct snd_util_memhdr {int dummy; } ;
struct snd_sf_sample {int /*<<< orphan*/ * block; } ;
struct snd_emux {struct snd_emu10k1* hw; } ;
struct snd_emu10k1 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_emu10k1_synth_free (struct snd_emu10k1*,int /*<<< orphan*/ *) ; 

int
snd_emu10k1_sample_free(struct snd_emux *rec, struct snd_sf_sample *sp,
			struct snd_util_memhdr *hdr)
{
	struct snd_emu10k1 *emu;

	emu = rec->hw;
	if (snd_BUG_ON(!sp || !hdr))
		return -EINVAL;

	if (sp->block) {
		snd_emu10k1_synth_free(emu, sp->block);
		sp->block = NULL;
	}
	return 0;
}