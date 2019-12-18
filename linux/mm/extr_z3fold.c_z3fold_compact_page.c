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
struct z3fold_header {scalar_t__ middle_chunks; scalar_t__ first_chunks; scalar_t__ last_chunks; scalar_t__ start_middle; int /*<<< orphan*/  first_num; } ;
struct page {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 scalar_t__ BIG_CHUNK_GAP ; 
 int /*<<< orphan*/  MIDDLE_CHUNK_MAPPED ; 
 int /*<<< orphan*/  PageIsolated (struct page*) ; 
 scalar_t__ TOTAL_CHUNKS ; 
 scalar_t__ ZHDR_CHUNKS ; 
 int /*<<< orphan*/  mchunk_memmove (struct z3fold_header*,unsigned short) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct page* virt_to_page (struct z3fold_header*) ; 

__attribute__((used)) static int z3fold_compact_page(struct z3fold_header *zhdr)
{
	struct page *page = virt_to_page(zhdr);

	if (test_bit(MIDDLE_CHUNK_MAPPED, &page->private))
		return 0; /* can't move middle chunk, it's used */

	if (unlikely(PageIsolated(page)))
		return 0;

	if (zhdr->middle_chunks == 0)
		return 0; /* nothing to compact */

	if (zhdr->first_chunks == 0 && zhdr->last_chunks == 0) {
		/* move to the beginning */
		mchunk_memmove(zhdr, ZHDR_CHUNKS);
		zhdr->first_chunks = zhdr->middle_chunks;
		zhdr->middle_chunks = 0;
		zhdr->start_middle = 0;
		zhdr->first_num++;
		return 1;
	}

	/*
	 * moving data is expensive, so let's only do that if
	 * there's substantial gain (at least BIG_CHUNK_GAP chunks)
	 */
	if (zhdr->first_chunks != 0 && zhdr->last_chunks == 0 &&
	    zhdr->start_middle - (zhdr->first_chunks + ZHDR_CHUNKS) >=
			BIG_CHUNK_GAP) {
		mchunk_memmove(zhdr, zhdr->first_chunks + ZHDR_CHUNKS);
		zhdr->start_middle = zhdr->first_chunks + ZHDR_CHUNKS;
		return 1;
	} else if (zhdr->last_chunks != 0 && zhdr->first_chunks == 0 &&
		   TOTAL_CHUNKS - (zhdr->last_chunks + zhdr->start_middle
					+ zhdr->middle_chunks) >=
			BIG_CHUNK_GAP) {
		unsigned short new_start = TOTAL_CHUNKS - zhdr->last_chunks -
			zhdr->middle_chunks;
		mchunk_memmove(zhdr, new_start);
		zhdr->start_middle = new_start;
		return 1;
	}

	return 0;
}