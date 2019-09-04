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
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct page {int dummy; } ;
struct hfsplus_sb_info {scalar_t__ total_blocks; int /*<<< orphan*/  alloc_mutex; int /*<<< orphan*/  free_blocks; TYPE_1__* alloc_file; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct address_space* i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP ; 
 int EIO ; 
 int ENOENT ; 
 struct hfsplus_sb_info* HFSPLUS_SB (struct super_block*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 scalar_t__ PAGE_CACHE_BITS ; 
 int /*<<< orphan*/  PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hfsplus_mark_mdb_dirty (struct super_block*) ; 
 int /*<<< orphan*/ * kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ) ; 
 struct page* read_mapping_page (struct address_space*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

int hfsplus_block_free(struct super_block *sb, u32 offset, u32 count)
{
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	struct page *page;
	struct address_space *mapping;
	__be32 *pptr, *curr, *end;
	u32 mask, len, pnr;
	int i;

	/* is there any actual work to be done? */
	if (!count)
		return 0;

	hfs_dbg(BITMAP, "block_free: %u,%u\n", offset, count);
	/* are all of the bits in range? */
	if ((offset + count) > sbi->total_blocks)
		return -ENOENT;

	mutex_lock(&sbi->alloc_mutex);
	mapping = sbi->alloc_file->i_mapping;
	pnr = offset / PAGE_CACHE_BITS;
	page = read_mapping_page(mapping, pnr, NULL);
	if (IS_ERR(page))
		goto kaboom;
	pptr = kmap(page);
	curr = pptr + (offset & (PAGE_CACHE_BITS - 1)) / 32;
	end = pptr + PAGE_CACHE_BITS / 32;
	len = count;

	/* do any partial u32 at the start */
	i = offset % 32;
	if (i) {
		int j = 32 - i;
		mask = 0xffffffffU << j;
		if (j > count) {
			mask |= 0xffffffffU >> (i + count);
			*curr++ &= cpu_to_be32(mask);
			goto out;
		}
		*curr++ &= cpu_to_be32(mask);
		count -= j;
	}

	/* do full u32s */
	while (1) {
		while (curr < end) {
			if (count < 32)
				goto done;
			*curr++ = 0;
			count -= 32;
		}
		if (!count)
			break;
		set_page_dirty(page);
		kunmap(page);
		page = read_mapping_page(mapping, ++pnr, NULL);
		if (IS_ERR(page))
			goto kaboom;
		pptr = kmap(page);
		curr = pptr;
		end = pptr + PAGE_CACHE_BITS / 32;
	}
done:
	/* do any partial u32 at end */
	if (count) {
		mask = 0xffffffffU >> count;
		*curr &= cpu_to_be32(mask);
	}
out:
	set_page_dirty(page);
	kunmap(page);
	sbi->free_blocks += len;
	hfsplus_mark_mdb_dirty(sb);
	mutex_unlock(&sbi->alloc_mutex);

	return 0;

kaboom:
	pr_crit("unable to mark blocks free: error %ld\n", PTR_ERR(page));
	mutex_unlock(&sbi->alloc_mutex);

	return -EIO;
}