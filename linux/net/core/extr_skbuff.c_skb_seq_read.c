#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct skb_seq_state {unsigned int lower_offset; unsigned int upper_offset; unsigned int stepped_offset; size_t frag_idx; TYPE_2__* cur_skb; TYPE_2__* root_skb; int /*<<< orphan*/ * frag_data; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {size_t nr_frags; TYPE_2__* frag_list; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/ * kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int skb_frag_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_page (int /*<<< orphan*/ *) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_has_frag_list (TYPE_2__*) ; 
 unsigned int skb_headlen (TYPE_2__*) ; 
 TYPE_1__* skb_shinfo (TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 

unsigned int skb_seq_read(unsigned int consumed, const u8 **data,
			  struct skb_seq_state *st)
{
	unsigned int block_limit, abs_offset = consumed + st->lower_offset;
	skb_frag_t *frag;

	if (unlikely(abs_offset >= st->upper_offset)) {
		if (st->frag_data) {
			kunmap_atomic(st->frag_data);
			st->frag_data = NULL;
		}
		return 0;
	}

next_skb:
	block_limit = skb_headlen(st->cur_skb) + st->stepped_offset;

	if (abs_offset < block_limit && !st->frag_data) {
		*data = st->cur_skb->data + (abs_offset - st->stepped_offset);
		return block_limit - abs_offset;
	}

	if (st->frag_idx == 0 && !st->frag_data)
		st->stepped_offset += skb_headlen(st->cur_skb);

	while (st->frag_idx < skb_shinfo(st->cur_skb)->nr_frags) {
		frag = &skb_shinfo(st->cur_skb)->frags[st->frag_idx];
		block_limit = skb_frag_size(frag) + st->stepped_offset;

		if (abs_offset < block_limit) {
			if (!st->frag_data)
				st->frag_data = kmap_atomic(skb_frag_page(frag));

			*data = (u8 *) st->frag_data + skb_frag_off(frag) +
				(abs_offset - st->stepped_offset);

			return block_limit - abs_offset;
		}

		if (st->frag_data) {
			kunmap_atomic(st->frag_data);
			st->frag_data = NULL;
		}

		st->frag_idx++;
		st->stepped_offset += skb_frag_size(frag);
	}

	if (st->frag_data) {
		kunmap_atomic(st->frag_data);
		st->frag_data = NULL;
	}

	if (st->root_skb == st->cur_skb && skb_has_frag_list(st->root_skb)) {
		st->cur_skb = skb_shinfo(st->root_skb)->frag_list;
		st->frag_idx = 0;
		goto next_skb;
	} else if (st->cur_skb->next) {
		st->cur_skb = st->cur_skb->next;
		st->frag_idx = 0;
		goto next_skb;
	}

	return 0;
}