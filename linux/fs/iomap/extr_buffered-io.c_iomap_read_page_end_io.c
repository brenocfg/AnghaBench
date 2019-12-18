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
struct iomap_page {int dummy; } ;
struct bio_vec {int /*<<< orphan*/  bv_len; int /*<<< orphan*/  bv_offset; struct page* bv_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  iomap_read_finish (struct iomap_page*,struct page*) ; 
 int /*<<< orphan*/  iomap_set_range_uptodate (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iomap_page* to_iomap_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
iomap_read_page_end_io(struct bio_vec *bvec, int error)
{
	struct page *page = bvec->bv_page;
	struct iomap_page *iop = to_iomap_page(page);

	if (unlikely(error)) {
		ClearPageUptodate(page);
		SetPageError(page);
	} else {
		iomap_set_range_uptodate(page, bvec->bv_offset, bvec->bv_len);
	}

	iomap_read_finish(iop, page);
}