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
struct list_head {int dummy; } ;
struct snd_util_memhdr {unsigned int used; int /*<<< orphan*/  nblocks; struct list_head block; scalar_t__ block_extra_size; } ;
struct snd_util_memblk {unsigned int offset; unsigned int size; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_util_memblk* get_memblk (struct list_head*) ; 
 struct snd_util_memblk* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 

struct snd_util_memblk *
__snd_util_memblk_new(struct snd_util_memhdr *hdr, unsigned int units,
		      struct list_head *prev)
{
	struct snd_util_memblk *blk;

	blk = kmalloc(sizeof(struct snd_util_memblk) + hdr->block_extra_size,
		      GFP_KERNEL);
	if (blk == NULL)
		return NULL;

	if (prev == &hdr->block)
		blk->offset = 0;
	else {
		struct snd_util_memblk *p = get_memblk(prev);
		blk->offset = p->offset + p->size;
	}
	blk->size = units;
	list_add(&blk->list, prev);
	hdr->nblocks++;
	hdr->used += units;
	return blk;
}