#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct orangefs_bufmap {int desc_size; int page_count; int desc_count; TYPE_1__* desc_array; int /*<<< orphan*/ * page_array; } ;
struct ORANGEFS_dev_map_desc {scalar_t__ ptr; } ;
struct TYPE_2__ {int array_count; scalar_t__ uaddr; int /*<<< orphan*/ * page_array; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FOLL_WRITE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (int /*<<< orphan*/ ) ; 
 int get_user_pages_fast (unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gossip_err (char*,int,int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
orangefs_bufmap_map(struct orangefs_bufmap *bufmap,
		struct ORANGEFS_dev_map_desc *user_desc)
{
	int pages_per_desc = bufmap->desc_size / PAGE_SIZE;
	int offset = 0, ret, i;

	/* map the pages */
	ret = get_user_pages_fast((unsigned long)user_desc->ptr,
			     bufmap->page_count, FOLL_WRITE, bufmap->page_array);

	if (ret < 0)
		return ret;

	if (ret != bufmap->page_count) {
		gossip_err("orangefs error: asked for %d pages, only got %d.\n",
				bufmap->page_count, ret);

		for (i = 0; i < ret; i++) {
			SetPageError(bufmap->page_array[i]);
			put_page(bufmap->page_array[i]);
		}
		return -ENOMEM;
	}

	/*
	 * ideally we want to get kernel space pointers for each page, but
	 * we can't kmap that many pages at once if highmem is being used.
	 * so instead, we just kmap/kunmap the page address each time the
	 * kaddr is needed.
	 */
	for (i = 0; i < bufmap->page_count; i++)
		flush_dcache_page(bufmap->page_array[i]);

	/* build a list of available descriptors */
	for (offset = 0, i = 0; i < bufmap->desc_count; i++) {
		bufmap->desc_array[i].page_array = &bufmap->page_array[offset];
		bufmap->desc_array[i].array_count = pages_per_desc;
		bufmap->desc_array[i].uaddr =
		    (user_desc->ptr + (i * pages_per_desc * PAGE_SIZE));
		offset += pages_per_desc;
	}

	return 0;
}