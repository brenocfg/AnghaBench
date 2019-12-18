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
struct extent_buffer {int /*<<< orphan*/  refs_lock; int /*<<< orphan*/  refs; int /*<<< orphan*/  bflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_BUFFER_TREE_REF ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_buffer_tree_ref(struct extent_buffer *eb)
{
	int refs;
	/* the ref bit is tricky.  We have to make sure it is set
	 * if we have the buffer dirty.   Otherwise the
	 * code to free a buffer can end up dropping a dirty
	 * page
	 *
	 * Once the ref bit is set, it won't go away while the
	 * buffer is dirty or in writeback, and it also won't
	 * go away while we have the reference count on the
	 * eb bumped.
	 *
	 * We can't just set the ref bit without bumping the
	 * ref on the eb because free_extent_buffer might
	 * see the ref bit and try to clear it.  If this happens
	 * free_extent_buffer might end up dropping our original
	 * ref by mistake and freeing the page before we are able
	 * to add one more ref.
	 *
	 * So bump the ref count first, then set the bit.  If someone
	 * beat us to it, drop the ref we added.
	 */
	refs = atomic_read(&eb->refs);
	if (refs >= 2 && test_bit(EXTENT_BUFFER_TREE_REF, &eb->bflags))
		return;

	spin_lock(&eb->refs_lock);
	if (!test_and_set_bit(EXTENT_BUFFER_TREE_REF, &eb->bflags))
		atomic_inc(&eb->refs);
	spin_unlock(&eb->refs_lock);
}