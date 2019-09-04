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
struct page {int dummy; } ;
struct inode {struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 size_t PAGE_SIZE ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  __GFP_FS ; 
 int /*<<< orphan*/  ceph_vinop (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,int /*<<< orphan*/ ,size_t,struct page*) ; 
 struct page* find_or_create_page (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  mapping_gfp_constraint (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,char*,size_t) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,size_t,size_t) ; 

void ceph_fill_inline_data(struct inode *inode, struct page *locked_page,
			   char	*data, size_t len)
{
	struct address_space *mapping = inode->i_mapping;
	struct page *page;

	if (locked_page) {
		page = locked_page;
	} else {
		if (i_size_read(inode) == 0)
			return;
		page = find_or_create_page(mapping, 0,
					   mapping_gfp_constraint(mapping,
					   ~__GFP_FS));
		if (!page)
			return;
		if (PageUptodate(page)) {
			unlock_page(page);
			put_page(page);
			return;
		}
	}

	dout("fill_inline_data %p %llx.%llx len %zu locked_page %p\n",
	     inode, ceph_vinop(inode), len, locked_page);

	if (len > 0) {
		void *kaddr = kmap_atomic(page);
		memcpy(kaddr, data, len);
		kunmap_atomic(kaddr);
	}

	if (page != locked_page) {
		if (len < PAGE_SIZE)
			zero_user_segment(page, len, PAGE_SIZE);
		else
			flush_dcache_page(page);

		SetPageUptodate(page);
		unlock_page(page);
		put_page(page);
	}
}