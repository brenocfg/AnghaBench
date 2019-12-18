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
struct page {TYPE_1__* mapping; scalar_t__ private; } ;
struct extent_buffer {int /*<<< orphan*/  refs_lock; int /*<<< orphan*/  bflags; int /*<<< orphan*/  refs; } ;
struct TYPE_2__ {int /*<<< orphan*/  private_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EXTENT_BUFFER_TREE_REF ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_buffer_under_io (struct extent_buffer*) ; 
 int release_extent_buffer (struct extent_buffer*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int try_release_extent_buffer(struct page *page)
{
	struct extent_buffer *eb;

	/*
	 * We need to make sure nobody is attaching this page to an eb right
	 * now.
	 */
	spin_lock(&page->mapping->private_lock);
	if (!PagePrivate(page)) {
		spin_unlock(&page->mapping->private_lock);
		return 1;
	}

	eb = (struct extent_buffer *)page->private;
	BUG_ON(!eb);

	/*
	 * This is a little awful but should be ok, we need to make sure that
	 * the eb doesn't disappear out from under us while we're looking at
	 * this page.
	 */
	spin_lock(&eb->refs_lock);
	if (atomic_read(&eb->refs) != 1 || extent_buffer_under_io(eb)) {
		spin_unlock(&eb->refs_lock);
		spin_unlock(&page->mapping->private_lock);
		return 0;
	}
	spin_unlock(&page->mapping->private_lock);

	/*
	 * If tree ref isn't set then we know the ref on this eb is a real ref,
	 * so just return, this page will likely be freed soon anyway.
	 */
	if (!test_and_clear_bit(EXTENT_BUFFER_TREE_REF, &eb->bflags)) {
		spin_unlock(&eb->refs_lock);
		return 0;
	}

	return release_extent_buffer(eb);
}