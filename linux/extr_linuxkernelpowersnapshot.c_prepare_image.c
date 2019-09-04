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
struct memory_bitmap {int dummy; } ;
struct linked_page {void* next; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PBES_PER_LINKED_PAGE ; 
 int /*<<< orphan*/  PG_SAFE ; 
 int /*<<< orphan*/  PG_UNSAFE_CLEAR ; 
 int /*<<< orphan*/  PG_UNSAFE_KEEP ; 
 unsigned int allocated_unsafe_pages ; 
 int /*<<< orphan*/ * buffer ; 
 unsigned int count_highmem_image_pages (struct memory_bitmap*) ; 
 int /*<<< orphan*/  duplicate_memory_bitmap (struct memory_bitmap*,struct memory_bitmap*) ; 
 int /*<<< orphan*/  free_image_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct linked_page* get_image_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_unsafe_pages (struct memory_bitmap*) ; 
 int memory_bm_create (struct memory_bitmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_bm_free (struct memory_bitmap*,int /*<<< orphan*/ ) ; 
 unsigned int nr_copy_pages ; 
 int prepare_highmem_image (struct memory_bitmap*,unsigned int*) ; 
 void* safe_pages_list ; 
 int /*<<< orphan*/  swsusp_free () ; 
 int /*<<< orphan*/  swsusp_page_is_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swsusp_set_page_forbidden (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swsusp_set_page_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (struct linked_page*) ; 

__attribute__((used)) static int prepare_image(struct memory_bitmap *new_bm, struct memory_bitmap *bm)
{
	unsigned int nr_pages, nr_highmem;
	struct linked_page *lp;
	int error;

	/* If there is no highmem, the buffer will not be necessary */
	free_image_page(buffer, PG_UNSAFE_CLEAR);
	buffer = NULL;

	nr_highmem = count_highmem_image_pages(bm);
	mark_unsafe_pages(bm);

	error = memory_bm_create(new_bm, GFP_ATOMIC, PG_SAFE);
	if (error)
		goto Free;

	duplicate_memory_bitmap(new_bm, bm);
	memory_bm_free(bm, PG_UNSAFE_KEEP);
	if (nr_highmem > 0) {
		error = prepare_highmem_image(bm, &nr_highmem);
		if (error)
			goto Free;
	}
	/*
	 * Reserve some safe pages for potential later use.
	 *
	 * NOTE: This way we make sure there will be enough safe pages for the
	 * chain_alloc() in get_buffer().  It is a bit wasteful, but
	 * nr_copy_pages cannot be greater than 50% of the memory anyway.
	 *
	 * nr_copy_pages cannot be less than allocated_unsafe_pages too.
	 */
	nr_pages = nr_copy_pages - nr_highmem - allocated_unsafe_pages;
	nr_pages = DIV_ROUND_UP(nr_pages, PBES_PER_LINKED_PAGE);
	while (nr_pages > 0) {
		lp = get_image_page(GFP_ATOMIC, PG_SAFE);
		if (!lp) {
			error = -ENOMEM;
			goto Free;
		}
		lp->next = safe_pages_list;
		safe_pages_list = lp;
		nr_pages--;
	}
	/* Preallocate memory for the image */
	nr_pages = nr_copy_pages - nr_highmem - allocated_unsafe_pages;
	while (nr_pages > 0) {
		lp = (struct linked_page *)get_zeroed_page(GFP_ATOMIC);
		if (!lp) {
			error = -ENOMEM;
			goto Free;
		}
		if (!swsusp_page_is_free(virt_to_page(lp))) {
			/* The page is "safe", add it to the list */
			lp->next = safe_pages_list;
			safe_pages_list = lp;
		}
		/* Mark the page as allocated */
		swsusp_set_page_forbidden(virt_to_page(lp));
		swsusp_set_page_free(virt_to_page(lp));
		nr_pages--;
	}
	return 0;

 Free:
	swsusp_free();
	return error;
}