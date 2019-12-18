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
struct snd_gf1_mem_block {struct snd_gf1_mem_block* name; struct snd_gf1_mem_block* next; struct snd_gf1_mem_block* prev; scalar_t__ share; } ;
struct snd_gf1_mem {struct snd_gf1_mem_block* last; struct snd_gf1_mem_block* first; int /*<<< orphan*/  memory_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_gf1_mem_block*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int snd_gf1_mem_xfree(struct snd_gf1_mem * alloc, struct snd_gf1_mem_block * block)
{
	if (block->share) {	/* ok.. shared block */
		block->share--;
		mutex_unlock(&alloc->memory_mutex);
		return 0;
	}
	if (alloc->first == block) {
		alloc->first = block->next;
		if (block->next)
			block->next->prev = NULL;
	} else {
		block->prev->next = block->next;
		if (block->next)
			block->next->prev = block->prev;
	}
	if (alloc->last == block) {
		alloc->last = block->prev;
		if (block->prev)
			block->prev->next = NULL;
	} else {
		block->next->prev = block->prev;
		if (block->prev)
			block->prev->next = block->next;
	}
	kfree(block->name);
	kfree(block);
	return 0;
}