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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  swp_entry_t ;
struct zswap_tree {int /*<<< orphan*/  lock; int /*<<< orphan*/  rbroot; } ;
struct zswap_header {int /*<<< orphan*/  swpentry; } ;
struct zswap_entry {scalar_t__ offset; TYPE_1__* pool; int /*<<< orphan*/  length; } ;
struct zpool {int dummy; } ;
struct writeback_control {int /*<<< orphan*/  sync_mode; } ;
struct page {int dummy; } ;
struct crypto_comp {int dummy; } ;
typedef  scalar_t__ pgoff_t ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EEXIST ; 
 int ENOMEM ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageReclaim (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  WB_SYNC_NONE ; 
 int /*<<< orphan*/  ZPOOL_MM_RO ; 
#define  ZSWAP_SWAPCACHE_EXIST 130 
#define  ZSWAP_SWAPCACHE_FAIL 129 
#define  ZSWAP_SWAPCACHE_NEW 128 
 int /*<<< orphan*/  __swap_writepage (struct page*,struct writeback_control*,int /*<<< orphan*/ ) ; 
 int crypto_comp_decompress (struct crypto_comp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  end_swap_bio_write ; 
 struct crypto_comp** get_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ swp_offset (int /*<<< orphan*/ ) ; 
 size_t swp_type (int /*<<< orphan*/ ) ; 
 struct zswap_header* zpool_map_handle (struct zpool*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_unmap_handle (struct zpool*,unsigned long) ; 
 struct zswap_entry* zswap_entry_find_get (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zswap_entry_put (struct zswap_tree*,struct zswap_entry*) ; 
 int zswap_get_swap_cache_page (int /*<<< orphan*/ ,struct page**) ; 
 struct zswap_entry* zswap_rb_search (int /*<<< orphan*/ *,scalar_t__) ; 
 struct zswap_tree** zswap_trees ; 
 int /*<<< orphan*/  zswap_written_back_pages ; 

__attribute__((used)) static int zswap_writeback_entry(struct zpool *pool, unsigned long handle)
{
	struct zswap_header *zhdr;
	swp_entry_t swpentry;
	struct zswap_tree *tree;
	pgoff_t offset;
	struct zswap_entry *entry;
	struct page *page;
	struct crypto_comp *tfm;
	u8 *src, *dst;
	unsigned int dlen;
	int ret;
	struct writeback_control wbc = {
		.sync_mode = WB_SYNC_NONE,
	};

	/* extract swpentry from data */
	zhdr = zpool_map_handle(pool, handle, ZPOOL_MM_RO);
	swpentry = zhdr->swpentry; /* here */
	tree = zswap_trees[swp_type(swpentry)];
	offset = swp_offset(swpentry);

	/* find and ref zswap entry */
	spin_lock(&tree->lock);
	entry = zswap_entry_find_get(&tree->rbroot, offset);
	if (!entry) {
		/* entry was invalidated */
		spin_unlock(&tree->lock);
		zpool_unmap_handle(pool, handle);
		return 0;
	}
	spin_unlock(&tree->lock);
	BUG_ON(offset != entry->offset);

	/* try to allocate swap cache page */
	switch (zswap_get_swap_cache_page(swpentry, &page)) {
	case ZSWAP_SWAPCACHE_FAIL: /* no memory or invalidate happened */
		ret = -ENOMEM;
		goto fail;

	case ZSWAP_SWAPCACHE_EXIST:
		/* page is already in the swap cache, ignore for now */
		put_page(page);
		ret = -EEXIST;
		goto fail;

	case ZSWAP_SWAPCACHE_NEW: /* page is locked */
		/* decompress */
		dlen = PAGE_SIZE;
		src = (u8 *)zhdr + sizeof(struct zswap_header);
		dst = kmap_atomic(page);
		tfm = *get_cpu_ptr(entry->pool->tfm);
		ret = crypto_comp_decompress(tfm, src, entry->length,
					     dst, &dlen);
		put_cpu_ptr(entry->pool->tfm);
		kunmap_atomic(dst);
		BUG_ON(ret);
		BUG_ON(dlen != PAGE_SIZE);

		/* page is up to date */
		SetPageUptodate(page);
	}

	/* move it to the tail of the inactive list after end_writeback */
	SetPageReclaim(page);

	/* start writeback */
	__swap_writepage(page, &wbc, end_swap_bio_write);
	put_page(page);
	zswap_written_back_pages++;

	spin_lock(&tree->lock);
	/* drop local reference */
	zswap_entry_put(tree, entry);

	/*
	* There are two possible situations for entry here:
	* (1) refcount is 1(normal case),  entry is valid and on the tree
	* (2) refcount is 0, entry is freed and not on the tree
	*     because invalidate happened during writeback
	*  search the tree and free the entry if find entry
	*/
	if (entry == zswap_rb_search(&tree->rbroot, offset))
		zswap_entry_put(tree, entry);
	spin_unlock(&tree->lock);

	goto end;

	/*
	* if we get here due to ZSWAP_SWAPCACHE_EXIST
	* a load may happening concurrently
	* it is safe and okay to not free the entry
	* if we free the entry in the following put
	* it it either okay to return !0
	*/
fail:
	spin_lock(&tree->lock);
	zswap_entry_put(tree, entry);
	spin_unlock(&tree->lock);

end:
	zpool_unmap_handle(pool, handle);
	return ret;
}