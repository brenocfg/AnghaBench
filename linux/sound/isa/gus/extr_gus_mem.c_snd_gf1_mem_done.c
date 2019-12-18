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
struct snd_gf1_mem {struct snd_gf1_mem_block* first; } ;
struct TYPE_2__ {struct snd_gf1_mem mem_alloc; } ;
struct snd_gus_card {TYPE_1__ gf1; } ;
struct snd_gf1_mem_block {struct snd_gf1_mem_block* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_gf1_mem_xfree (struct snd_gf1_mem*,struct snd_gf1_mem_block*) ; 

int snd_gf1_mem_done(struct snd_gus_card * gus)
{
	struct snd_gf1_mem *alloc;
	struct snd_gf1_mem_block *block, *nblock;

	alloc = &gus->gf1.mem_alloc;
	block = alloc->first;
	while (block) {
		nblock = block->next;
		snd_gf1_mem_xfree(alloc, block);
		block = nblock;
	}
	return 0;
}