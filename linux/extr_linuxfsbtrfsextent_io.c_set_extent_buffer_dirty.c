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
struct extent_buffer {int /*<<< orphan*/ * pages; int /*<<< orphan*/  bflags; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_BUFFER_DIRTY ; 
 int /*<<< orphan*/  EXTENT_BUFFER_TREE_REF ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_buffer_tree_ref (struct extent_buffer*) ; 
 int num_extent_pages (struct extent_buffer*) ; 
 int /*<<< orphan*/  set_page_dirty (int /*<<< orphan*/ ) ; 
 int test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int set_extent_buffer_dirty(struct extent_buffer *eb)
{
	int i;
	int num_pages;
	int was_dirty = 0;

	check_buffer_tree_ref(eb);

	was_dirty = test_and_set_bit(EXTENT_BUFFER_DIRTY, &eb->bflags);

	num_pages = num_extent_pages(eb);
	WARN_ON(atomic_read(&eb->refs) == 0);
	WARN_ON(!test_bit(EXTENT_BUFFER_TREE_REF, &eb->bflags));

	for (i = 0; i < num_pages; i++)
		set_page_dirty(eb->pages[i]);
	return was_dirty;
}