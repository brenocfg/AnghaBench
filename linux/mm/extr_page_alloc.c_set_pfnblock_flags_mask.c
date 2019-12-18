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
struct page {int dummy; } ;

/* Variables and functions */
 unsigned long BITS_PER_LONG ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int MIGRATE_TYPES ; 
 int NR_PAGEBLOCK_BITS ; 
 int PB_migratetype_bits ; 
 unsigned long READ_ONCE (unsigned long) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 unsigned long cmpxchg (unsigned long*,unsigned long,unsigned long) ; 
 unsigned long* get_pageblock_bitmap (struct page*,unsigned long) ; 
 int /*<<< orphan*/  page_zone (struct page*) ; 
 unsigned long pfn_to_bitidx (struct page*,unsigned long) ; 
 int /*<<< orphan*/  zone_spans_pfn (int /*<<< orphan*/ ,unsigned long) ; 

void set_pfnblock_flags_mask(struct page *page, unsigned long flags,
					unsigned long pfn,
					unsigned long end_bitidx,
					unsigned long mask)
{
	unsigned long *bitmap;
	unsigned long bitidx, word_bitidx;
	unsigned long old_word, word;

	BUILD_BUG_ON(NR_PAGEBLOCK_BITS != 4);
	BUILD_BUG_ON(MIGRATE_TYPES > (1 << PB_migratetype_bits));

	bitmap = get_pageblock_bitmap(page, pfn);
	bitidx = pfn_to_bitidx(page, pfn);
	word_bitidx = bitidx / BITS_PER_LONG;
	bitidx &= (BITS_PER_LONG-1);

	VM_BUG_ON_PAGE(!zone_spans_pfn(page_zone(page), pfn), page);

	bitidx += end_bitidx;
	mask <<= (BITS_PER_LONG - bitidx - 1);
	flags <<= (BITS_PER_LONG - bitidx - 1);

	word = READ_ONCE(bitmap[word_bitidx]);
	for (;;) {
		old_word = cmpxchg(&bitmap[word_bitidx], word, (word & ~mask) | flags);
		if (word == old_word)
			break;
		word = old_word;
	}
}