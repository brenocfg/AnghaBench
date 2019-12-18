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
struct zswap_tree {int /*<<< orphan*/  lock; int /*<<< orphan*/  rbroot; } ;
struct zswap_header {int dummy; } ;
struct zswap_entry {int /*<<< orphan*/  handle; TYPE_1__* pool; int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;
struct page {int dummy; } ;
struct crypto_comp {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
struct TYPE_2__ {int /*<<< orphan*/  zpool; int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  ZPOOL_MM_RO ; 
 int crypto_comp_decompress (struct crypto_comp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*) ; 
 struct crypto_comp** get_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_evictable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zpool_map_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_unmap_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct zswap_entry* zswap_entry_find_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zswap_entry_put (struct zswap_tree*,struct zswap_entry*) ; 
 int /*<<< orphan*/  zswap_fill_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct zswap_tree** zswap_trees ; 

__attribute__((used)) static int zswap_frontswap_load(unsigned type, pgoff_t offset,
				struct page *page)
{
	struct zswap_tree *tree = zswap_trees[type];
	struct zswap_entry *entry;
	struct crypto_comp *tfm;
	u8 *src, *dst;
	unsigned int dlen;
	int ret;

	/* find */
	spin_lock(&tree->lock);
	entry = zswap_entry_find_get(&tree->rbroot, offset);
	if (!entry) {
		/* entry was written back */
		spin_unlock(&tree->lock);
		return -1;
	}
	spin_unlock(&tree->lock);

	if (!entry->length) {
		dst = kmap_atomic(page);
		zswap_fill_page(dst, entry->value);
		kunmap_atomic(dst);
		goto freeentry;
	}

	/* decompress */
	dlen = PAGE_SIZE;
	src = zpool_map_handle(entry->pool->zpool, entry->handle, ZPOOL_MM_RO);
	if (zpool_evictable(entry->pool->zpool))
		src += sizeof(struct zswap_header);
	dst = kmap_atomic(page);
	tfm = *get_cpu_ptr(entry->pool->tfm);
	ret = crypto_comp_decompress(tfm, src, entry->length, dst, &dlen);
	put_cpu_ptr(entry->pool->tfm);
	kunmap_atomic(dst);
	zpool_unmap_handle(entry->pool->zpool, entry->handle);
	BUG_ON(ret);

freeentry:
	spin_lock(&tree->lock);
	zswap_entry_put(tree, entry);
	spin_unlock(&tree->lock);

	return 0;
}