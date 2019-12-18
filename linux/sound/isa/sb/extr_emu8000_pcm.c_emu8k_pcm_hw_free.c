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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_emu8k_pcm {int voices; int /*<<< orphan*/ * block; TYPE_2__* emu; scalar_t__ dram_opened; } ;
struct TYPE_4__ {int /*<<< orphan*/  memhdr; } ;
struct TYPE_3__ {struct snd_emu8k_pcm* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  emu8k_close_dram (TYPE_2__*) ; 
 int /*<<< orphan*/  snd_util_mem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_voice (struct snd_emu8k_pcm*,int) ; 

__attribute__((used)) static int emu8k_pcm_hw_free(struct snd_pcm_substream *subs)
{
	struct snd_emu8k_pcm *rec = subs->runtime->private_data;

	if (rec->block) {
		int ch;
		for (ch = 0; ch < rec->voices; ch++)
			stop_voice(rec, ch); // to be sure
		if (rec->dram_opened)
			emu8k_close_dram(rec->emu);
		snd_util_mem_free(rec->emu->memhdr, rec->block);
		rec->block = NULL;
	}
	return 0;
}