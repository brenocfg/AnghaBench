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
struct orangefs_write_range {scalar_t__ pos; size_t len; void* gid; void* uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cancel_dirty_page (struct page*) ; 
 void* current_fsgid () ; 
 void* current_fsuid () ; 
 int /*<<< orphan*/  kfree (struct orangefs_write_range*) ; 
 int /*<<< orphan*/  orangefs_launder_page (struct page*) ; 
 scalar_t__ page_offset (struct page*) ; 
 scalar_t__ page_private (struct page*) ; 
 int /*<<< orphan*/  printk (char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void orangefs_invalidatepage(struct page *page,
				 unsigned int offset,
				 unsigned int length)
{
	struct orangefs_write_range *wr;
	wr = (struct orangefs_write_range *)page_private(page);

	if (offset == 0 && length == PAGE_SIZE) {
		kfree((struct orangefs_write_range *)page_private(page));
		set_page_private(page, 0);
		ClearPagePrivate(page);
		put_page(page);
		return;
	/* write range entirely within invalidate range (or equal) */
	} else if (page_offset(page) + offset <= wr->pos &&
	    wr->pos + wr->len <= page_offset(page) + offset + length) {
		kfree((struct orangefs_write_range *)page_private(page));
		set_page_private(page, 0);
		ClearPagePrivate(page);
		put_page(page);
		/* XXX is this right? only caller in fs */
		cancel_dirty_page(page);
		return;
	/* invalidate range chops off end of write range */
	} else if (wr->pos < page_offset(page) + offset &&
	    wr->pos + wr->len <= page_offset(page) + offset + length &&
	     page_offset(page) + offset < wr->pos + wr->len) {
		size_t x;
		x = wr->pos + wr->len - (page_offset(page) + offset);
		WARN_ON(x > wr->len);
		wr->len -= x;
		wr->uid = current_fsuid();
		wr->gid = current_fsgid();
	/* invalidate range chops off beginning of write range */
	} else if (page_offset(page) + offset <= wr->pos &&
	    page_offset(page) + offset + length < wr->pos + wr->len &&
	    wr->pos < page_offset(page) + offset + length) {
		size_t x;
		x = page_offset(page) + offset + length - wr->pos;
		WARN_ON(x > wr->len);
		wr->pos += x;
		wr->len -= x;
		wr->uid = current_fsuid();
		wr->gid = current_fsgid();
	/* invalidate range entirely within write range (punch hole) */
	} else if (wr->pos < page_offset(page) + offset &&
	    page_offset(page) + offset + length < wr->pos + wr->len) {
		/* XXX what do we do here... should not WARN_ON */
		WARN_ON(1);
		/* punch hole */
		/*
		 * should we just ignore this and write it out anyway?
		 * it hardly makes sense
		 */
		return;
	/* non-overlapping ranges */
	} else {
		/* WARN if they do overlap */
		if (!((page_offset(page) + offset + length <= wr->pos) ^
		    (wr->pos + wr->len <= page_offset(page) + offset))) {
			WARN_ON(1);
			printk("invalidate range offset %llu length %u\n",
			    page_offset(page) + offset, length);
			printk("write range offset %llu length %zu\n",
			    wr->pos, wr->len);
		}
		return;
	}

	/*
	 * Above there are returns where wr is freed or where we WARN.
	 * Thus the following runs if wr was modified above.
	 */

	orangefs_launder_page(page);
}