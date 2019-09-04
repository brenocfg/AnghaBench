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
typedef  unsigned long u64 ;
struct page {scalar_t__ private; } ;
struct extent_buffer {struct page** pages; int /*<<< orphan*/  refs; int /*<<< orphan*/  bflags; } ;
struct btrfs_fs_info {unsigned long nodesize; int /*<<< orphan*/  buffer_lock; int /*<<< orphan*/  buffer_radix; int /*<<< orphan*/  sectorsize; TYPE_1__* btree_inode; } ;
struct address_space {int /*<<< orphan*/  private_lock; } ;
struct TYPE_2__ {struct address_space* i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct extent_buffer* ERR_PTR (int) ; 
 int /*<<< orphan*/  EXTENT_BUFFER_IN_TREE ; 
 int /*<<< orphan*/  EXTENT_BUFFER_UPTODATE ; 
 int GFP_NOFS ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SHIFT ; 
 int PageDirty (struct page*) ; 
 scalar_t__ PagePrivate (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __GFP_NOFAIL ; 
 struct extent_buffer* __alloc_extent_buffer (struct btrfs_fs_info*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  attach_extent_buffer_page (struct extent_buffer*,struct page*) ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,unsigned long) ; 
 int /*<<< orphan*/  btrfs_release_extent_buffer (struct extent_buffer*) ; 
 int /*<<< orphan*/  check_buffer_tree_ref (struct extent_buffer*) ; 
 struct extent_buffer* find_extent_buffer (struct btrfs_fs_info*,unsigned long) ; 
 struct page* find_or_create_page (struct address_space*,unsigned long,int) ; 
 int /*<<< orphan*/  mark_extent_buffer_accessed (struct extent_buffer*,struct page*) ; 
 int num_extent_pages (struct extent_buffer*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,unsigned long,struct extent_buffer*) ; 
 int radix_tree_preload (int) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

struct extent_buffer *alloc_extent_buffer(struct btrfs_fs_info *fs_info,
					  u64 start)
{
	unsigned long len = fs_info->nodesize;
	int num_pages;
	int i;
	unsigned long index = start >> PAGE_SHIFT;
	struct extent_buffer *eb;
	struct extent_buffer *exists = NULL;
	struct page *p;
	struct address_space *mapping = fs_info->btree_inode->i_mapping;
	int uptodate = 1;
	int ret;

	if (!IS_ALIGNED(start, fs_info->sectorsize)) {
		btrfs_err(fs_info, "bad tree block start %llu", start);
		return ERR_PTR(-EINVAL);
	}

	eb = find_extent_buffer(fs_info, start);
	if (eb)
		return eb;

	eb = __alloc_extent_buffer(fs_info, start, len);
	if (!eb)
		return ERR_PTR(-ENOMEM);

	num_pages = num_extent_pages(eb);
	for (i = 0; i < num_pages; i++, index++) {
		p = find_or_create_page(mapping, index, GFP_NOFS|__GFP_NOFAIL);
		if (!p) {
			exists = ERR_PTR(-ENOMEM);
			goto free_eb;
		}

		spin_lock(&mapping->private_lock);
		if (PagePrivate(p)) {
			/*
			 * We could have already allocated an eb for this page
			 * and attached one so lets see if we can get a ref on
			 * the existing eb, and if we can we know it's good and
			 * we can just return that one, else we know we can just
			 * overwrite page->private.
			 */
			exists = (struct extent_buffer *)p->private;
			if (atomic_inc_not_zero(&exists->refs)) {
				spin_unlock(&mapping->private_lock);
				unlock_page(p);
				put_page(p);
				mark_extent_buffer_accessed(exists, p);
				goto free_eb;
			}
			exists = NULL;

			/*
			 * Do this so attach doesn't complain and we need to
			 * drop the ref the old guy had.
			 */
			ClearPagePrivate(p);
			WARN_ON(PageDirty(p));
			put_page(p);
		}
		attach_extent_buffer_page(eb, p);
		spin_unlock(&mapping->private_lock);
		WARN_ON(PageDirty(p));
		eb->pages[i] = p;
		if (!PageUptodate(p))
			uptodate = 0;

		/*
		 * We can't unlock the pages just yet since the extent buffer
		 * hasn't been properly inserted in the radix tree, this
		 * opens a race with btree_releasepage which can free a page
		 * while we are still filling in all pages for the buffer and
		 * we could crash.
		 */
	}
	if (uptodate)
		set_bit(EXTENT_BUFFER_UPTODATE, &eb->bflags);
again:
	ret = radix_tree_preload(GFP_NOFS);
	if (ret) {
		exists = ERR_PTR(ret);
		goto free_eb;
	}

	spin_lock(&fs_info->buffer_lock);
	ret = radix_tree_insert(&fs_info->buffer_radix,
				start >> PAGE_SHIFT, eb);
	spin_unlock(&fs_info->buffer_lock);
	radix_tree_preload_end();
	if (ret == -EEXIST) {
		exists = find_extent_buffer(fs_info, start);
		if (exists)
			goto free_eb;
		else
			goto again;
	}
	/* add one reference for the tree */
	check_buffer_tree_ref(eb);
	set_bit(EXTENT_BUFFER_IN_TREE, &eb->bflags);

	/*
	 * Now it's safe to unlock the pages because any calls to
	 * btree_releasepage will correctly detect that a page belongs to a
	 * live buffer and won't free them prematurely.
	 */
	for (i = 0; i < num_pages; i++)
		unlock_page(eb->pages[i]);
	return eb;

free_eb:
	WARN_ON(!atomic_dec_and_test(&eb->refs));
	for (i = 0; i < num_pages; i++) {
		if (eb->pages[i])
			unlock_page(eb->pages[i]);
	}

	btrfs_release_extent_buffer(eb);
	return exists;
}