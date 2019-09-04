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
struct snd_emux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_util_mem_free (struct snd_util_memhdr*,int /*<<< orphan*/ *) ; 

int
snd_emu8000_sample_free(struct snd_emux *rec, struct snd_sf_sample *sp,
			struct snd_util_memhdr *hdr)
{
	if (sp->block) {
		snd_util_mem_free(hdr, sp->block);
		sp->block = NULL;
	}
	return 0;
}