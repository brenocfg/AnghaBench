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
struct snd_gf1_mem_block {int /*<<< orphan*/  share_id; struct snd_gf1_mem_block* next; } ;
struct snd_gf1_mem {struct snd_gf1_mem_block* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct snd_gf1_mem_block *snd_gf1_mem_share(struct snd_gf1_mem * alloc,
					      unsigned int *share_id)
{
	struct snd_gf1_mem_block *block;

	if (!share_id[0] && !share_id[1] &&
	    !share_id[2] && !share_id[3])
		return NULL;
	for (block = alloc->first; block; block = block->next)
		if (!memcmp(share_id, block->share_id,
				sizeof(block->share_id)))
			return block;
	return NULL;
}