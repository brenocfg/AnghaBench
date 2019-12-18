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
struct page {int /*<<< orphan*/  mapping; } ;
struct file {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  erofs_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (struct bio*) ; 
 scalar_t__ IS_ERR (struct bio*) ; 
 int PTR_ERR (struct bio*) ; 
 struct bio* erofs_read_raw_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  trace_erofs_readpage (struct page*,int) ; 

__attribute__((used)) static int erofs_raw_access_readpage(struct file *file, struct page *page)
{
	erofs_off_t last_block;
	struct bio *bio;

	trace_erofs_readpage(page, true);

	bio = erofs_read_raw_page(NULL, page->mapping,
				  page, &last_block, 1, false);

	if (IS_ERR(bio))
		return PTR_ERR(bio);

	DBG_BUGON(bio);	/* since we have only one bio -- must be NULL */
	return 0;
}