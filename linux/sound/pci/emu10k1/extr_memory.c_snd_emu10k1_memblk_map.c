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
struct snd_emu10k1_memblk {scalar_t__ mapped_page; int pages; scalar_t__ map_locked; int /*<<< orphan*/  mapped_order_link; } ;
struct list_head {struct list_head* next; } ;
struct snd_emu10k1 {int /*<<< orphan*/  memblk_lock; struct list_head mapped_order_link_head; } ;

/* Variables and functions */
 struct snd_emu10k1_memblk* get_emu10k1_memblk (struct list_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int map_memblk (struct snd_emu10k1*,struct snd_emu10k1_memblk*) ; 
 int /*<<< orphan*/  mapped_order_link ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int unmap_memblk (struct snd_emu10k1*,struct snd_emu10k1_memblk*) ; 

int snd_emu10k1_memblk_map(struct snd_emu10k1 *emu, struct snd_emu10k1_memblk *blk)
{
	int err;
	int size;
	struct list_head *p, *nextp;
	struct snd_emu10k1_memblk *deleted;
	unsigned long flags;

	spin_lock_irqsave(&emu->memblk_lock, flags);
	if (blk->mapped_page >= 0) {
		/* update order link */
		list_move_tail(&blk->mapped_order_link,
			       &emu->mapped_order_link_head);
		spin_unlock_irqrestore(&emu->memblk_lock, flags);
		return 0;
	}
	if ((err = map_memblk(emu, blk)) < 0) {
		/* no enough page - try to unmap some blocks */
		/* starting from the oldest block */
		p = emu->mapped_order_link_head.next;
		for (; p != &emu->mapped_order_link_head; p = nextp) {
			nextp = p->next;
			deleted = get_emu10k1_memblk(p, mapped_order_link);
			if (deleted->map_locked)
				continue;
			size = unmap_memblk(emu, deleted);
			if (size >= blk->pages) {
				/* ok the empty region is enough large */
				err = map_memblk(emu, blk);
				break;
			}
		}
	}
	spin_unlock_irqrestore(&emu->memblk_lock, flags);
	return err;
}